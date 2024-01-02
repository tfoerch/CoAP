#ifndef LIBS_IPCC_FACTORYIF_HPP_
#define LIBS_IPCC_FACTORYIF_HPP_
/*
 * IPCCFactoryIF.hpp
 *
 *  Created on: 11.03.2015
 *      Author: tom
 */

#include <boost/asio/ip/udp.hpp>

namespace boost { namespace asio { class io_context; } }

namespace lmp
{
  namespace cc
  {
    class IpccMsgReceiveIF;

    class IpccFactoryIF
    {
    public:
      inline IpccMsgReceiveIF const* getIpcc(
        const boost::asio::ip::udp::endpoint&  sender_endpoint) const
      { return do_getIpcc(sender_endpoint); }
      inline IpccMsgReceiveIF* accessIpcc(
        const boost::asio::ip::udp::endpoint&  sender_endpoint)
      { return do_accessIpcc(sender_endpoint); }
      inline IpccMsgReceiveIF* createIpcc(
        const boost::asio::ip::udp::endpoint&  sender_endpoint,
        NetworkIFSocketIF&                     networkIFSocket,
        boost::asio::io_context&               io_context)
      {  return do_createIpcc(sender_endpoint, networkIFSocket, io_context); }
      inline bool removeIpcc(
        const boost::asio::ip::udp::endpoint&  sender_endpoint)
      {  return do_removeIpcc(sender_endpoint); }
      virtual ~IpccFactoryIF(){}
    private:
      virtual IpccMsgReceiveIF const* do_getIpcc(
        const boost::asio::ip::udp::endpoint&  sender_endpoint) const = 0;
      virtual IpccMsgReceiveIF* do_accessIpcc(
        const boost::asio::ip::udp::endpoint&  sender_endpoint) = 0;
      virtual IpccMsgReceiveIF* do_createIpcc(
        const boost::asio::ip::udp::endpoint&  sender_endpoint,
        NetworkIFSocketIF&                     networkIFSocket,
        boost::asio::io_context&               io_context) = 0;
      virtual bool do_removeIpcc(
        const boost::asio::ip::udp::endpoint&  sender_endpoint) = 0;
    };
  } // namespace cc
} // namespace lmp


#endif /* LIBS_IPCC_FACTORYIF_HPP_ */
