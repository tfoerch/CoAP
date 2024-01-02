#include <lmp_mgtif_netif.hpp>
#include <lmp_mgtif_node.hpp>
#include <lmp_mgtif_ipcc.hpp>                // for IPCC_var, IPCC_ptr
#include <lmp_mgtif_ipcc_adjacency_observer.hpp>      // for Neighbor_var, etc
#include <Mgt_UDPMsgReceiveIFProxy.hpp>
#include <Mgt_NetworkIFProxy.hpp>
#include <Mgt_IPCCAdjacencyChangeFtorIF.hpp>
#include <Mgt_IPCCInDestructionFtorIF.hpp>
#include "cc/IPCC_NetIFSocket.hpp"

#include <omniORB4/CORBA.h>  // for Long, Short
#include <omniORB4/poa.h>    // for POA_ptr

#include <boost/asio/ip/udp.hpp>

#include <map>
#include <set>

namespace lmp_node
{
  class NodeApplProxy;
  class NetworkIFInDestructionFtorIF;
}

namespace lmp_netif
{
  class NetworkIF_i : public POA_lmp_netif::NetworkIF
  {
  public:
    NetworkIF_i(
      PortableServer::POA_ptr                  poa,
      lmp_node::NodeApplProxy&                 node,
      boost::asio::io_context&                 io_context,
      const std::string&                       ifName,
      lmp::WORD                                port,
      lmp_node::NetworkIFInDestructionFtorIF&  networkIFInDestructionFtor);
    virtual ~NetworkIF_i();
    virtual char* getInterfaceName();
    virtual ::CORBA::Short getLocalPortNumber();
    virtual ::CORBA::Long getNodeId();
    virtual void destroy();
    virtual void enable();
    virtual void disable();
    virtual ::lmp_ipcc::IPCC_ptr createIPCC(
      ::CORBA::Long remoteAddress,
      ::CORBA::Short remotePortNumber);
    virtual ::lmp_ipcc::IPCC_ptr getIPCC(
      ::CORBA::Long remoteAddress,
      ::CORBA::Short remotePortNumber);
    virtual void deleteIPCC(
      ::CORBA::Long remoteAddress,
      ::CORBA::Short remotePortNumber);
    virtual void registerIPCCAdjacencyObserver(
      ::lmp_ipcc_adjacency_observer::IPCCAdjacencyObserver_ptr observer);
    virtual void deregisterIPCCAdjacencyObserver(
      ::lmp_ipcc_adjacency_observer::IPCCAdjacencyObserver_ptr observer);
  private:
    typedef  std::map<boost::asio::ip::udp::endpoint, ::lmp_ipcc::IPCC_var>       IPCCByRemoteEndPointMap;
    typedef  std::set<::lmp_ipcc_adjacency_observer::IPCCAdjacencyObserver_var>   IPCCAdjacencyObserverContainer;
    class IPCCAdjDiscoveredFtor : public IPCCAdjacencyChangeFtorIF
    {
    public:
      explicit IPCCAdjDiscoveredFtor(
        NetworkIF_i&  networkIF);
    private:
      virtual void do_process(
        const boost::asio::ip::udp::endpoint&  sender_endpointl);
      NetworkIF_i&  m_networkIF;
    };
    class IPCCInDestructionFtor : public IPCCInDestructionFtorIF
    {
    public:
      explicit IPCCInDestructionFtor(
        NetworkIF_i&  networkIF);
    private:
      virtual void do_process(
        lmp::DWORD                   remoteAddress,
        lmp::WORD                    remotePortNumber);
      NetworkIF_i&  m_networkIF;
    };
    PortableServer::POA_ptr                  m_POA;
    lmp_node::NodeApplProxy&                 m_node;
    boost::asio::io_context&                 m_io_context;
    IPCCByRemoteEndPointMap                  m_IPCCs;
    IPCCAdjacencyObserverContainer           m_ipccAdjacencyObservers;
    IPCCAdjDiscoveredFtor                    m_ipccAdjDiscoveredFtor;
    IPCCInDestructionFtor                    m_ipccInDestructionFtor;
    lmp_netif::UDPMsgReceiveIFProxy          m_msgHandler;
    lmp::cc::NetworkIFSocket                 m_networkIfSocket;
    lmp_netif::NetworkIFProxy                m_networkIfProxy;
    lmp_node::NetworkIFInDestructionFtorIF&  m_networkIFInDestructionFtor;
  };

} // end namespace LMP
