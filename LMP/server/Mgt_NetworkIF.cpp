#include <Mgt_NetworkIF.hpp>
#include <Mgt_IPCC.hpp>
#include "Mgt_NetworkIFInDestructionFtorIF.hpp"

#include <iostream>                     // for operator<<, etc

namespace lmp_netif
{

NetworkIF_i::NetworkIF_i(
  PortableServer::POA_ptr                  poa,
  lmp_node::NodeApplProxy&                 node,
  boost::asio::io_context&                 io_context,
  const std::string&                       ifName,
  lmp::WORD                                port,
  lmp_node::NetworkIFInDestructionFtorIF&  networkIFInDestructionFtor)
  : m_POA(PortableServer::POA::_duplicate(poa)),
    m_node(node),
    m_io_context(io_context),
    m_ipccAdjDiscoveredFtor(*this),
    m_ipccInDestructionFtor(*this),
    m_msgHandler(m_node, m_ipccAdjDiscoveredFtor),
    m_networkIfSocket(m_io_context, ifName, port, m_msgHandler, false),
    m_networkIfProxy(m_networkIfSocket),
    m_networkIFInDestructionFtor(networkIFInDestructionFtor)
{
  std::cout << "Node(" << m_node.getNodeId() << ").NetworkIF(ifName = '" << m_networkIfSocket.getIfName() << "', portNumber = " << m_networkIfSocket.getLocalPortNumber() << ')' << std::endl;
}

NetworkIF_i::~NetworkIF_i()
{
  std::cout << "Node(" << m_node.getNodeId() << ").NetworkIF(ifName = '" << m_networkIfSocket.getIfName() << "', portNumber = " << m_networkIfSocket.getLocalPortNumber() << ") destructor" << std::endl;
}

char* NetworkIF_i::getInterfaceName()
{
  return CORBA::string_dup(m_networkIfSocket.getIfName().c_str());
}

::CORBA::Short NetworkIF_i::getLocalPortNumber()
{
  return m_networkIfSocket.getLocalPortNumber();
}

::CORBA::Long NetworkIF_i::getNodeId()
{
  return m_node.getNodeId();
}

void NetworkIF_i::destroy()
{
  std::cout << "Node(" << m_node.getNodeId() << ").NetworkIF(ifName = '" << m_networkIfSocket.getIfName() << "', portNumber = " << m_networkIfSocket.getLocalPortNumber() << ") destroy" << std::endl;
  m_networkIFInDestructionFtor(m_networkIfSocket.getIfName(), m_networkIfSocket.getLocalPortNumber());
  // TODO theNodePtr->deleteNetworkIF(m_localCCId);
  PortableServer::ObjectId *oid = m_POA->servant_to_id(this);
  m_POA->deactivate_object(*oid);  delete oid;
  _remove_ref(); // delete this;
  std::cout << "Node(" << m_node.getNodeId() << ").NetworkIF(ifName = '" << m_networkIfSocket.getIfName() << "', portNumber = " << m_networkIfSocket.getLocalPortNumber() << ") destroy finished" << std::endl;
}

void NetworkIF_i::enable()
{
  std::cout << "Node(" << m_node.getNodeId() << ").NetworkIF(ifName = '" << m_networkIfSocket.getIfName() << "', portNumber = " << m_networkIfSocket.getLocalPortNumber() << ") enable" << std::endl;
  m_networkIfProxy.enable();
  // m_msgHandler.setNetworkIFObjRef(this->_this());
}

void NetworkIF_i::disable()
{
  std::cout << "Node(" << m_node.getNodeId() << ").NetworkIF(ifName = '" << m_networkIfSocket.getIfName() << "', portNumber = " << m_networkIfSocket.getLocalPortNumber() << ") disable" << std::endl;
  m_networkIfProxy.disable();
  // m_msgHandler.clearNetworkIFObjRef();
}


lmp_ipcc::IPCC_ptr NetworkIF_i::createIPCC(
  ::CORBA::Long   remoteAddress,
  ::CORBA::Short  remotePortNumber)
{
  boost::asio::ip::address_v4  ipv4(remoteAddress);
  boost::asio::ip::udp::endpoint remote_endpoint(ipv4, remotePortNumber);

  IPCCByRemoteEndPointMap::const_iterator ipccIter = m_IPCCs.find(remote_endpoint);
  if (ipccIter == m_IPCCs.end())
  {
    lmp::cc::IpccMsgReceiveIF* ipccPtr =
      m_msgHandler.createIpcc(remote_endpoint, m_networkIfProxy, m_io_context);
    if (ipccPtr)
    {
      lmp::cc::IpccApplicationIF* ipccApplPtr =
        dynamic_cast<lmp::cc::IpccApplicationIF*>(ipccPtr);
      if (ipccApplPtr)
      {
        lmp_ipcc::IPCC_i* servant =
          new lmp_ipcc::IPCC_i(m_POA, m_node, m_networkIfProxy, *ipccApplPtr, m_ipccInDestructionFtor);
        PortableServer::ObjectId *oid = m_POA->activate_object(servant);  delete oid;
        lmp_ipcc::IPCC_ptr ipcc = servant->_this();
        // servant->_remove_ref();
        ipccIter = m_IPCCs.insert(IPCCByRemoteEndPointMap::value_type(remote_endpoint, lmp_ipcc::IPCC::_duplicate(ipcc))).first;
        if (ipccIter != m_IPCCs.end())
        {
          lmp_ipcc::IPCC_ptr ipcc_ptr = ipccIter->second;
          if (ipcc_ptr)
          {
            for (IPCCAdjacencyObserverContainer::const_iterator obsIter = m_ipccAdjacencyObservers.begin();
                obsIter != m_ipccAdjacencyObservers.end();
                ++obsIter)
            {
              if (*obsIter)
              {
                ::lmp_ipcc_adjacency_observer::IPCCAdjacencyObserver_var observer = *obsIter;
                observer->ipccAdjacencyAdded(ipcc_ptr);
              }
            }
          }
          return ipcc_ptr;
        }
      }
    }
  }
  throw lmp_netif::Entity_Already_Exists();
}

lmp_ipcc::IPCC_ptr NetworkIF_i::getIPCC(
  ::CORBA::Long remoteAddress,
  ::CORBA::Short remotePortNumber)
{
  boost::asio::ip::address_v4  ipv4(remoteAddress);
  boost::asio::ip::udp::endpoint remote_endpoint(ipv4, remotePortNumber);
  IPCCByRemoteEndPointMap::const_iterator ipccIter = m_IPCCs.find(remote_endpoint);
  if (ipccIter != m_IPCCs.end())
  {
    return ipccIter->second;
  }
  throw lmp_netif::No_Such_Entity();
}

void NetworkIF_i::deleteIPCC(
  ::CORBA::Long remoteAddress,
  ::CORBA::Short remotePortNumber)
{
  boost::asio::ip::address_v4  ipv4(remoteAddress);
  boost::asio::ip::udp::endpoint remote_endpoint(ipv4, remotePortNumber);
  IPCCByRemoteEndPointMap::iterator ipccIter = m_IPCCs.find(remote_endpoint);
  if (ipccIter != m_IPCCs.end())
  {
    lmp_ipcc::IPCC_ptr ipcc_ptr = ipccIter->second;
    if (ipcc_ptr)
    {
      for (IPCCAdjacencyObserverContainer::const_iterator obsIter = m_ipccAdjacencyObservers.begin();
          obsIter != m_ipccAdjacencyObservers.end();
          ++obsIter)
      {
        if (*obsIter)
        {
          ::lmp_ipcc_adjacency_observer::IPCCAdjacencyObserver_var observer = *obsIter;
          observer->ipccAdjacencyRemoved(ipcc_ptr);
        }
      }
    }
    m_IPCCs.erase(ipccIter);
    return;
  }
  throw lmp_netif::No_Such_Entity();
}

void NetworkIF_i::registerIPCCAdjacencyObserver(
  ::lmp_ipcc_adjacency_observer::IPCCAdjacencyObserver_ptr observer)
{
  std::cout << "Node(" << m_node.getNodeId()
            << ").NetworkIF(ifName = '" << m_networkIfSocket.getIfName() << "', portNumber = " << m_networkIfSocket.getLocalPortNumber() << ").registerIPCCAdjacencyObserver()" << std::endl;
  m_ipccAdjacencyObservers.insert(lmp_ipcc_adjacency_observer::IPCCAdjacencyObserver::_duplicate(observer));
}

void NetworkIF_i::deregisterIPCCAdjacencyObserver(
  ::lmp_ipcc_adjacency_observer::IPCCAdjacencyObserver_ptr observer)
{
  std::cout << "Node(" << m_node.getNodeId()
            << ").NetworkIF(ifName = '" << m_networkIfSocket.getIfName() << "', portNumber = " << m_networkIfSocket.getLocalPortNumber() << ").deregisterIPCCAdjacencyObserver()" << std::endl;
  m_ipccAdjacencyObservers.erase(lmp_ipcc_adjacency_observer::IPCCAdjacencyObserver::_duplicate(observer));
}

NetworkIF_i::IPCCAdjDiscoveredFtor::IPCCAdjDiscoveredFtor(
  NetworkIF_i&  networkIF)
: m_networkIF(networkIF)
{
}

void NetworkIF_i::IPCCAdjDiscoveredFtor::do_process(
  const boost::asio::ip::udp::endpoint&  sender_endpointl)
{
  if (sender_endpointl.address().is_v4())
  {
    m_networkIF.createIPCC(sender_endpointl.address().to_v4().to_ulong(),
                           sender_endpointl.port());
  }
}

NetworkIF_i::IPCCInDestructionFtor::IPCCInDestructionFtor(
  NetworkIF_i&  networkIF)
: m_networkIF(networkIF)
{
}

void NetworkIF_i::IPCCInDestructionFtor::do_process(
  lmp::DWORD                   remoteAddress,
  lmp::WORD                    remotePortNumber)
{
  try
  {
    std::cout << "calling delete" << std::endl;
    m_networkIF.deleteIPCC(remoteAddress, remotePortNumber);
  }
  catch(lmp_netif::No_Such_Entity& nsE)
  {
  }
}


} // end namespace lmp_netif
