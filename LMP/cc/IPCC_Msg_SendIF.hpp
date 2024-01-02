#ifndef LMP_CC_MSG_SENDIF_HPP_
#define LMP_CC_MSG_SENDIF_HPP_
/*
 * IPCC_Msg_SendIF.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "msg/MessageAst.hpp"

#include <boost/asio/ip/udp.hpp>

namespace lmp
{
  namespace cc
  {
    class IpccMsgSendIF
    {
    public:
      inline void sendMessage(
        const boost::asio::ip::udp::endpoint&  destination_endpoint,
        const msg::ast::Message&               message)
      { do_sendMessage(destination_endpoint, message); }
      virtual ~IpccMsgSendIF(){}
    private:
      virtual void do_sendMessage(
        const boost::asio::ip::udp::endpoint&  destination_endpoint,
        const msg::ast::Message&               message) = 0;
    };
  } // namespace cc
} // namespace lmp

#endif /* LMP_CC_MSG_SENDIF_HPP_ */
