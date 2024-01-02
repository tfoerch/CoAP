#ifndef Server_NetworkIF_Proxy_HPP_
#define Server_NetworkIF_Proxy_HPP_
/*
 * Mgt_NetworkIFProxy.hpp
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include "cc/NetworkIFSocketIF.hpp"
#include <lmp_mgtif_netif.hpp>

namespace lmp_netif
{

  class NetworkIFProxy : public lmp::cc::NetworkIFSocketIF
  {
  public:
    explicit NetworkIFProxy(
      lmp::cc::NetworkIFSocketIF&    networkIf);
    virtual ~NetworkIFProxy(){}
  private:
    // implement NetworkIFSocketIF
    virtual const std::string& do_getIfName() const;
    virtual lmp::WORD do_getLocalPortNumber() const;
    virtual void do_enable();
    virtual void do_disable();
    virtual void do_send(
      const boost::asio::ip::udp::endpoint&  destination_endpoint,
      boost::asio::mutable_buffers_1&        messageBuffer);

    lmp::cc::NetworkIFSocketIF&   m_networkIf;
  };

} // end namespace lmp_netif

#endif /* Server_NetworkIF_Proxy_HPP_ */
