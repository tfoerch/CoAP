#ifndef TEST_IPCC_MSG_RECEIVER_HPP_
#define TEST_IPCC_MSG_RECEIVER_HPP_
/*
 * Test_IPCC_Msg_Receiver.hpp
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include <IPCC_Msg_ReceiveIF.hpp>
#include <CheckFtorIF.hpp>

namespace lmp
{
  namespace cc
  {
	class TestIpccMsgReceiver : public IpccMsgReceiveIF
	{
	public:
	  class MsgReceivedFtor : public lmp::base::CheckFtorIF
	  {
	  public:
	    MsgReceivedFtor();
	    MsgReceivedFtor(
	      const MsgReceivedFtor&  other);
	    void reset();
	    void set();
	  private:
	    virtual bool do_check() const;
	    virtual CheckFtorIF* do_clone() const;
	    bool m_check_flag;
	  };
	  void reset();
	  const lmp::base::CheckFtorIF& getConfigMessageReceivedFtor() const;
	  const lmp::base::CheckFtorIF& getConfigAckMessageReceivedFtor() const;
	  const lmp::base::CheckFtorIF& getConfigNackMessageReceivedFtor() const;
	  const lmp::base::CheckFtorIF& getHelloMessageReceivedFtor() const;
	private:
	  virtual void do_processReceivedMessage(
	    const msg::ast::Config&                  configMsg);
	  virtual void do_processReceivedMessage(
	    const msg::ast::ConfigAck&               configAckMsg);
	  virtual void do_processReceivedMessage(
	    const msg::ast::ConfigNack&              configNackMsg);
	  virtual void do_processReceivedMessage(
	    const msg::ast::Hello&                   helloMsg);
	  MsgReceivedFtor  m_ConfigMessageReceivedFtor;
	  MsgReceivedFtor  m_ConfigAckMessageReceivedFtor;
	  MsgReceivedFtor  m_ConfigNackMessageReceivedFtor;
	  MsgReceivedFtor  m_HelloMessageReceivedFtor;
	};
  } // namespace cc
} // namespace lmp

#endif /* TEST_IPCC_MSG_RECEIVER_HPP_ */
