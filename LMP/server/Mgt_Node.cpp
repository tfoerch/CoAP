#include <Mgt_Node.hpp>
#include <Mgt_Neighbor.hpp>
#include <Mgt_NetworkIF.hpp>
#include "lmp_mgtif_node.hpp"           // for No_Such_Entity, etc
#include "lmp_mgtif_node_registry.hpp"  // for NodeRegistry_var, etc
#include "lmp_mgtif_neighbor_adjacency_observer.hpp"

#include <boost/bind.hpp>
#include <iostream>

namespace lmp_node
{

Node_i::Node_i(
  CORBA::ORB_ptr           orb,
  PortableServer::POA_ptr  poa,
  ::CORBA::Long            nodeId,
  ::lmp_node_registry::NodeRegistry_ptr  aNodeRegistry)
: theORB(CORBA::ORB::_duplicate(orb)),
  m_POA(PortableServer::POA::_duplicate(poa)),
  m_io_service(),
  m_work(m_io_service),
  m_threadPool(),
  m_node(nodeId),
  theNodeRegistry(::lmp_node_registry::NodeRegistry::_duplicate(aNodeRegistry)),
  m_networkIFsByIfName(),
  m_neighborAdjacencyObserver(),
  m_neighborByNodeIdMap(),
  m_neighborAdjAddedFtor(*this,
                         m_neighborAdjacencyObserver),
  m_neighborAdjRemovedFtor(*this,
                           m_neighborAdjacencyObserver),
  m_networkIFInDestructionFtor(*this),
  m_nodeProxy(m_node,
              m_neighborAdjAddedFtor,
              m_neighborAdjRemovedFtor)
{
  std::cout << "Node(" << m_node.getNodeId()
            << ") ctor " << std::endl;
//  std::cout << "ctor activate object" << std::endl;
//  PortableServer::ObjectId_var myNodeId = m_POA->activate_object(this);
//  std::cout << "ctor object activated" << std::endl;
  //this->_remove_ref();
  //PortableServer::ObjectId *oid=m_POA->activate_object(this); delete oid;

  for(size_t t = 0;
      t < 1; // std::thread::hardware_concurrency();
      ++t)
  {
    m_threadPool.push_back(std::thread(boost::bind(&boost::asio::io_service::run,
                                                   &m_io_service)));
  }

}

Node_i::~Node_i()
{
  std::cout << "Node(" << m_node.getNodeId()
            << ") dtor " << std::endl;
  CORBA::release(m_POA);
  CORBA::release(theORB);
}

::CORBA::Long Node_i::getNodeId()
{
  return m_node.getNodeId();
}

lmp_netif::NetworkIF_ptr Node_i::createNetworkIF(
  const char*     interfaceName,
  ::CORBA::Short  localPortNumber)
{
  std::cout << "Node(" << m_node.getNodeId()
            << ").createNetworkIF(ifName = " << interfaceName
            << ", localPortNumber = " << localPortNumber << ')' << std::endl;
  std::string  ifName(interfaceName);
  NetworkIFKey  networkIFKey(ifName, localPortNumber);
  NetworkIFByIfNameMap::iterator netIfIter = m_networkIFsByIfName.find(networkIFKey);
      if (m_networkIFsByIfName.find(networkIFKey) == m_networkIFsByIfName.end())
  {
    lmp_netif::NetworkIF_i* servant =
      new lmp_netif::NetworkIF_i(m_POA,
                                 m_nodeProxy,
                                 m_io_service,
                                 ifName,
                                 localPortNumber,
                                 m_networkIFInDestructionFtor);
    PortableServer::ObjectId *oid = m_POA->activate_object(servant);  delete oid;
    lmp_netif::NetworkIF_ptr netif = servant->_this();
    netIfIter =
      m_networkIFsByIfName.insert(NetworkIFByIfNameMap::value_type(networkIFKey,
                                                                      lmp_netif::NetworkIF::_duplicate(netif))).first;
    return netIfIter->second;
  }
  throw lmp_node::Entity_Already_Exists();

}

lmp_netif::NetworkIF_ptr Node_i::getNetworkIF(
  const char*     interfaceName,
  ::CORBA::Short  localPortNumber)
{
  std::string  ifName(interfaceName);
  NetworkIFKey  networkIFKey(ifName, localPortNumber);
  NetworkIFByIfNameMap::const_iterator netIfIter = m_networkIFsByIfName.find(networkIFKey);
  if (netIfIter != m_networkIFsByIfName.end())
  {
    return netIfIter->second;
  }
  throw lmp_node::No_Such_Entity();
}

void Node_i::deleteNetworkIF(
  const char*     interfaceName,
  ::CORBA::Short  localPortNumber)
{
  std::string  ifName(interfaceName);
  NetworkIFKey  networkIFKey(ifName, localPortNumber);
  NetworkIFByIfNameMap::iterator netIfIter = m_networkIFsByIfName.find(networkIFKey);
  if (netIfIter != m_networkIFsByIfName.end())
  {
    m_networkIFsByIfName.erase(netIfIter);
    return;
  }
  throw lmp_node::No_Such_Entity();
}

void Node_i::registerNeighborAdjacencyObserver(
  ::lmp_neighbor_adjacency_observer::NeighborAdjacencyObserver_ptr observer)
{
  std::cout << "Node(" << m_node.getNodeId()
            << ").registerNeighborAdjacencyObserver()" << std::endl;
  m_neighborAdjacencyObserver.insert(lmp_neighbor_adjacency_observer::NeighborAdjacencyObserver::_duplicate(observer));
}

void Node_i::deregisterNeighborAdjacencyObserver(
  ::lmp_neighbor_adjacency_observer::NeighborAdjacencyObserver_ptr observer)
{
  std::cout << "Node(" << m_node.getNodeId()
            << ").deregisterNeighborAdjacencyObserver()" << std::endl;
  m_neighborAdjacencyObserver.erase(lmp_neighbor_adjacency_observer::NeighborAdjacencyObserver::_duplicate(observer));
}

lmp_neighbor::Neighbor_ptr Node_i::createNeighbor(
  ::CORBA::Long remoteNodeId)
{
  NeighborByNodeIdMap::iterator neighborIter = m_neighborByNodeIdMap.find(remoteNodeId);
  if (neighborIter == m_neighborByNodeIdMap.end())
  {
    lmp::neighbor::NeighborApplicationIF* neighborPtr = m_node.createNeighbor(remoteNodeId);
    if (neighborPtr)
    {
      lmp_neighbor::Neighbor_i* servant = new lmp_neighbor::Neighbor_i(m_POA, m_nodeProxy, *neighborPtr);
      PortableServer::ObjectId *oid = m_POA->activate_object(servant);  delete oid;
      lmp_neighbor::Neighbor_ptr neighbor = servant->_this();
      neighborIter = m_neighborByNodeIdMap.insert(NeighborByNodeIdMap::value_type(remoteNodeId,
                                                                                  lmp_neighbor::Neighbor::_duplicate(neighbor))).first;
      return neighborIter->second;
    }
  }
  throw lmp_node::Entity_Already_Exists();
}

lmp_neighbor::Neighbor_ptr Node_i::getNeighbor(
  ::CORBA::Long remoteNodeId)
{
  NeighborByNodeIdMap::const_iterator neighborIter = m_neighborByNodeIdMap.find(remoteNodeId);
  if (neighborIter != m_neighborByNodeIdMap.end())
  {
    return neighborIter->second;
  }
  throw lmp_node::No_Such_Entity();
}

void Node_i::deleteNeighbor(
 ::CORBA::Long remoteNodeId)
{
  NeighborByNodeIdMap::iterator neighborIter = m_neighborByNodeIdMap.find(remoteNodeId);
  if (neighborIter != m_neighborByNodeIdMap.end())
  {
    m_neighborByNodeIdMap.erase(neighborIter);
  }
  throw lmp_node::No_Such_Entity();
}

void Node_i::destroy()
{
  std::cout << "Node(" << m_node.getNodeId()
            << ") destroy before stop" << std::endl;
  m_io_service.stop();
  std::cout << "Node(" << m_node.getNodeId()
            << ") destroy after stop" << std::endl;
  for(std::thread& t : m_threadPool)
  {
    t.join();
  }

  if (!CORBA::is_nil(theNodeRegistry))
  {
    theNodeRegistry->deregisterNode(this->_this());
  }
  PortableServer::ObjectId *oid = m_POA->servant_to_id(this);
  std::cout << "Node(" << m_node.getNodeId()
            << ") destroy before deactivate_object" << std::endl;
  m_POA->deactivate_object(*oid);  delete oid;
  std::cout << "Node(" << m_node.getNodeId()
            << ") destroy before after deactivate_object" << std::endl;
  // _remove_ref(); // delete this;
  // std::cout << "after _remove_ref" << std::endl;
  // Shutdown the ORB (but do not wait for completion).  This also
  // causes the main thread to unblock from CORBA::ORB::run().
  theORB->shutdown(0);
}

Node_i::NeighborAdjAddedFtor::NeighborAdjAddedFtor(
  Node_i&                              node,
  NeighborAdjacencyObserverContainer&  observers)
: m_node(node),
  m_observers(observers)
{
}

void Node_i::NeighborAdjAddedFtor::do_process(
  lmp::DWORD                   neighborNodeId,
  lmp::cc::IpccApplicationIF&  ipcc)
{
  std::cout << "Node[" << m_node.getNodeId() << "]::NeighborAdjAddedFtor("
            << neighborNodeId << ") called" << std::endl;
  ::lmp_neighbor::Neighbor_var neighborRef = lmp_neighbor::Neighbor::_duplicate(m_node.createNeighbor(neighborNodeId));
  for (NeighborAdjacencyObserverContainer::const_iterator iter = m_observers.begin(),
                                                          end_iter = m_observers.end();
       iter != end_iter;
       ++iter)
  {
    (*iter)->neighborAdjacencyAdded(neighborRef);
  }
}

Node_i::NeighborAdjRemovedFtor::NeighborAdjRemovedFtor(
    Node_i&                            node,
  NeighborAdjacencyObserverContainer&  observers)
: m_node(node),
  m_observers(observers)
{
}

void Node_i::NeighborAdjRemovedFtor::do_process(
  lmp::DWORD                   neighborNodeId,
  lmp::cc::IpccApplicationIF&  ipcc)
{
}

Node_i::NetworkIFInDestructionFtor::NetworkIFInDestructionFtor(
  Node_i&  node)
: m_node(node)
{
}

void Node_i::NetworkIFInDestructionFtor::do_process(
    const std::string&  ifName,
    lmp::WORD           localPortNumber)
{
  try
  {
    m_node.deleteNetworkIF(ifName.c_str(), localPortNumber);
  }
  catch(lmp_node::No_Such_Entity& nsE)
  {
  }
}


} // end namespace lmp_node
