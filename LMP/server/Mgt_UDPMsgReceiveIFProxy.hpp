#ifndef Server_UDPMsgReceiveIF_Proxy_HPP_
#define Server_UDPMsgReceiveIF_Proxy_HPP_
/*
 * Mgt_UDPMsgReceiveIFProxy.hpp
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include "cc/UDP_Msg_ReceiveIF.hpp"
#include "cc/IPCCFactoryIF.hpp"
#include "cc/UDP_Msg_Handler.hpp"
#include <lmp_mgtif_node.hpp>
#include <lmp_mgtif_netif.hpp>

namespace lmp_node
{
  class NodeApplProxy;
}

namespace lmp_netif
{
  class IPCCAdjacencyChangeFtorIF;

  class UDPMsgReceiveIFProxy : public lmp::cc::UDPMsgReceiveIF,
                               public lmp::cc::IpccFactoryIF
  {
  public:
    UDPMsgReceiveIFProxy(
      lmp_node::NodeApplProxy&    node,
      IPCCAdjacencyChangeFtorIF&  ipccAdjDiscoveredFtor);
    virtual ~UDPMsgReceiveIFProxy(){}
  private:
    // implement UDPMsgReceiveIF
    virtual void do_processReceivedMessage(
      lmp::cc::NetworkIFSocketIF&            networkIFSocket,
      boost::asio::io_context&               io_context,
      const boost::asio::ip::udp::endpoint&  sender_endpoint,
      boost::asio::const_buffers_1&          messageBuffer);
    // implement IpccFactoryIF
    virtual lmp::cc::IpccMsgReceiveIF const* do_getIpcc(
      const boost::asio::ip::udp::endpoint&  sender_endpoint) const;
    virtual lmp::cc::IpccMsgReceiveIF* do_accessIpcc(
      const boost::asio::ip::udp::endpoint&  sender_endpoint);
    virtual lmp::cc::IpccMsgReceiveIF* do_createIpcc(
      const boost::asio::ip::udp::endpoint&  sender_endpoint,
      lmp::cc::NetworkIFSocketIF&            networkIFSocket,
      boost::asio::io_context&               io_context);
    virtual bool do_removeIpcc(
      const boost::asio::ip::udp::endpoint&  sender_endpoint);

    lmp_node::NodeApplProxy&    m_node;
    lmp::cc::UDPMsgHandler      m_udpMsgHandler;
    IPCCAdjacencyChangeFtorIF&  m_ipccAdjDiscoveredFtor;
  };

} // end namespace LMP

#endif /* Server_UDPMsgReceiveIF_Proxy_HPP_ */
