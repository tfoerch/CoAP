#ifndef LIBS_IPCC_NETIFSOCKET_HPP_
#define LIBS_IPCC_NETIFSOCKET_HPP_
/*
 * IPCC_NetIFSocket.hpp
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include "NetworkIFSocketIF.hpp"

#include "base/ProtocolTypes.hpp"             // for DWORD
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/optional/optional.hpp>        // for optional

namespace boost { namespace asio { class io_context; } }

namespace lmp
{
  namespace cc
  {
    class UDPMsgReceiveIF;

    class NetworkIFSocket : public NetworkIFSocketIF
    {
    public:
      NetworkIFSocket(
    	boost::asio::io_context&          io_context,
        const std::string&                ifName,
        lmp::WORD                         port,
        UDPMsgReceiveIF&                  udpMsgHandler,
        bool                              bind2Interface); // bind socket to interface device
     virtual ~NetworkIFSocket();
      typedef boost::optional<boost::asio::ip::address_v4> OptAddressV4;
      typedef boost::optional<boost::asio::ip::address_v6> OptAddressV6;
      typedef std::pair<OptAddressV4, OptAddressV6>        OptAddresses;
      static OptAddresses getIfAddress(
        const std::string&                ifName);
    private:
      NetworkIFSocket(
        NetworkIFSocket&&  other) = default;
      // implement NetworkIFSocketIF
      virtual const std::string& do_getIfName() const;
      virtual lmp::WORD do_getLocalPortNumber() const;
      virtual void do_enable();
      virtual void do_disable();
      virtual void do_send(
        const boost::asio::ip::udp::endpoint&  destination_endpoint,
        boost::asio::mutable_buffers_1&        messageBuffer);
      void start_receive();
      void handle_received_msg(
    	const boost::system::error_code&  error,
        size_t                            bytes_recvd);
      void handle_send_msg(
    	const boost::system::error_code&  error,
    	size_t                            bytes_sent);
      boost::asio::io_context&                       m_io_context;
      UDPMsgReceiveIF&                               m_udpMsgHandler;
      std::string                                    m_ifName;
      lmp::WORD                                      m_port;
      bool                                           m_bind2Interface;
      boost::asio::ip::udp::socket                   m_socket;
      boost::asio::ip::udp::endpoint                 m_sender_endpoint;
      enum { max_buffer_length = 4096 };
      char                                           m_buffer[max_buffer_length] = {};
      static const boost::asio::ip::address          c_multicast_address;
    };
  } // namespace cc
} // namespace lmp

#endif /* LIBS_IPCC_NETIFSOCKET_HPP_ */
