#include <Mgt_NetworkIFProxy.hpp>
#include <iostream>

namespace lmp_netif
{
  NetworkIFProxy::NetworkIFProxy(
    lmp::cc::NetworkIFSocketIF&    networkIf)
  : m_networkIf(networkIf)
  {
  }

  const std::string& NetworkIFProxy::do_getIfName() const
  {
    return m_networkIf.getIfName();
  }
  lmp::WORD NetworkIFProxy::do_getLocalPortNumber() const
  {
    return m_networkIf.getLocalPortNumber();
  }

  void NetworkIFProxy::do_enable()
  {
    m_networkIf.enable();
  }

  void NetworkIFProxy::do_disable()
  {
    m_networkIf.disable();
  }

  void NetworkIFProxy::do_send(
      const boost::asio::ip::udp::endpoint&  destination_endpoint,
      boost::asio::mutable_buffers_1&        messageBuffer)
  {
    m_networkIf.send(destination_endpoint, messageBuffer);
  }

} // end namespace lmp_netif
