#ifndef Server_IPCCAdjacencyFtorIF_HPP_
#define Server_IPCCAdjacencyFtorIF_HPP_
/*
 * Mgt_IPCCAdjacencyChangeFtorIF.hpp
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include <boost/asio/ip/udp.hpp>

namespace lmp_netif
{

  class IPCCAdjacencyChangeFtorIF
  {
  public:
    inline void operator()(
      const boost::asio::ip::udp::endpoint&  sender_endpoint)
    { do_process(sender_endpoint); }
    virtual ~IPCCAdjacencyChangeFtorIF(){}
  private:
    virtual void do_process(
      const boost::asio::ip::udp::endpoint&  sender_endpointl) = 0;
  };

} // end namespace lmp_netif

#endif /* Server_IPCCAdjacencyFtorIF_HPP_ */
