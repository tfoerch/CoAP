#include <Mgt_UDPMsgReceiveIFProxy.hpp>
#include <Mgt_NodeApplProxy.hpp>
#include <Mgt_IPCCAdjacencyChangeFtorIF.hpp>
#include <lmp_mgtif_ipcc.hpp>

#include "base/ProtocolTypes.hpp"                  // for DWORD

#include <iostream>

namespace lmp_netif
{
  UDPMsgReceiveIFProxy::UDPMsgReceiveIFProxy(
    lmp_node::NodeApplProxy&    node,
    IPCCAdjacencyChangeFtorIF&  ipccAdjDiscoveredFtor)
  : m_node(node),
    m_udpMsgHandler(m_node),
    m_ipccAdjDiscoveredFtor(ipccAdjDiscoveredFtor)
  {
  }

  void UDPMsgReceiveIFProxy::do_processReceivedMessage(
    lmp::cc::NetworkIFSocketIF&            networkIFSocket,
    boost::asio::io_context&               io_context,
    const boost::asio::ip::udp::endpoint&  sender_endpoint,
    boost::asio::const_buffers_1&          messageBuffer)
  {
    lmp::cc::IpccMsgReceiveIF* ipccPtr =
      m_udpMsgHandler.accessIpcc(sender_endpoint);
    if (!ipccPtr)
    {
      m_ipccAdjDiscoveredFtor(sender_endpoint);
      ipccPtr =
        m_udpMsgHandler.accessIpcc(sender_endpoint);
    }
    if (ipccPtr)
    {
      m_udpMsgHandler.processReceivedMessage(networkIFSocket,
                                             io_context,
                                             sender_endpoint,
                                             messageBuffer);
    }
  }

  lmp::cc::IpccMsgReceiveIF const* UDPMsgReceiveIFProxy::do_getIpcc(
    const boost::asio::ip::udp::endpoint&  sender_endpoint) const
  {
    return m_udpMsgHandler.getIpcc(sender_endpoint);
  }

  lmp::cc::IpccMsgReceiveIF* UDPMsgReceiveIFProxy::do_accessIpcc(
    const boost::asio::ip::udp::endpoint&  sender_endpoint)
  {
    return m_udpMsgHandler.accessIpcc(sender_endpoint);
  }

  lmp::cc::IpccMsgReceiveIF* UDPMsgReceiveIFProxy::do_createIpcc(
    const boost::asio::ip::udp::endpoint&  sender_endpoint,
    lmp::cc::NetworkIFSocketIF&            networkIFSocket,
    boost::asio::io_context&               io_context)
  {
    return m_udpMsgHandler.createIpcc(sender_endpoint, networkIFSocket, io_context);
  }

  bool UDPMsgReceiveIFProxy::do_removeIpcc(
    const boost::asio::ip::udp::endpoint&  sender_endpoint)
  {
    return m_udpMsgHandler.removeIpcc(sender_endpoint);
  }

} // end namespace lmp_netif
