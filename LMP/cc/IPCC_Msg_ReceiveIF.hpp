#ifndef LMP_CC_MSG_RECEIVEIF_HPP_
#define LMP_CC_MSG_RECEIVEIF_HPP_
/*
 * IPCC_Msg_ReceiveIF.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

//#include "msg/Config.hpp"
//#include "msg/ConfigAck.hpp"
//#include "msg/ConfigNack.hpp"
//#include "msg/Hello.hpp"
//#include "msg/UnknownMessage.hpp"

// http://www.boost.org/doc/libs/1_57_0/libs/ptr_container/doc/guidelines.html
namespace lmp
{
  namespace msg
  {
    namespace ast
    {
      struct Config;
      struct ConfigAck;
      struct ConfigNack;
      struct Hello;
      struct UnknownMessage;
    }
  }
  namespace cc
  {
    class IpccMsgReceiveIF
    {
    public:
      inline void processReceivedMessage(
    	const msg::ast::Config&                  configMsg)
      { do_processReceivedMessage(configMsg); }
      inline void processReceivedMessage(
    	const msg::ast::ConfigAck&               configAckMsg)
      { do_processReceivedMessage(configAckMsg); }
      inline void processReceivedMessage(
    	const msg::ast::ConfigNack&              configNackMsg)
      { do_processReceivedMessage(configNackMsg); }
      inline void processReceivedMessage(
    	const msg::ast::Hello&                   helloMsg)
      { do_processReceivedMessage(helloMsg); }
      inline void processReceivedMessage(
        const msg::ast::UnknownMessage&             unknownMessage)
      { do_processReceivedMessage(unknownMessage); }
      virtual ~IpccMsgReceiveIF(){}
    private:
      virtual void do_processReceivedMessage(
    	const msg::ast::Config&                  configMsg) = 0;
      virtual void do_processReceivedMessage(
    	const msg::ast::ConfigAck&               configAckMsg) = 0;
      virtual void do_processReceivedMessage(
    	const msg::ast::ConfigNack&              configNackMsg) = 0;
      virtual void do_processReceivedMessage(
    	const msg::ast::Hello&                   helloMsg) = 0;
      virtual void do_processReceivedMessage(
        const msg::ast::UnknownMessage&             unknownMessage) = 0;
    };
  } // namespace cc
} // namespace lmp

#endif /* LMP_CC_MSG_RECEIVEIF_HPP_ */
