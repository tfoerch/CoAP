/*
 * IPCC_Impl.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "Test_IPCC_Msg_Receiver.hpp"

namespace lmp
{
  namespace cc
  {
    void TestIpccMsgReceiver::reset()
    {
      m_ConfigMessageReceivedFtor.reset();
      m_ConfigAckMessageReceivedFtor.reset();
      m_ConfigNackMessageReceivedFtor.reset();
      m_HelloMessageReceivedFtor.reset();
    }
    const lmp::base::CheckFtorIF& TestIpccMsgReceiver::getConfigMessageReceivedFtor() const
    {
      return m_ConfigMessageReceivedFtor;
    }

    const lmp::base::CheckFtorIF& TestIpccMsgReceiver::getConfigAckMessageReceivedFtor() const
    {
      return m_ConfigAckMessageReceivedFtor;
    }

    const lmp::base::CheckFtorIF& TestIpccMsgReceiver::getConfigNackMessageReceivedFtor() const
    {
      return m_ConfigNackMessageReceivedFtor;
    }

    const lmp::base::CheckFtorIF& TestIpccMsgReceiver::getHelloMessageReceivedFtor() const
    {
      return m_HelloMessageReceivedFtor;
    }

    void TestIpccMsgReceiver::do_processReceivedMessage(
      const msg::ast::Config&      configMsg)
    {
      m_ConfigMessageReceivedFtor.set();
    }

    void TestIpccMsgReceiver::do_processReceivedMessage(
      const msg::ast::ConfigAck&   configAckMsg)
    {
      m_ConfigAckMessageReceivedFtor.set();
    }

    void TestIpccMsgReceiver::do_processReceivedMessage(
      const msg::ast::ConfigNack&  configNackMsg)
    {
      m_ConfigNackMessageReceivedFtor.set();
    }

    void TestIpccMsgReceiver::do_processReceivedMessage(
      const msg::ast::Hello&       helloMsg)
    {
      m_HelloMessageReceivedFtor.set();
    }

    TestIpccMsgReceiver::MsgReceivedFtor::MsgReceivedFtor()
    : CheckFtorIF(),
      m_check_flag(false)
    {
    }

    TestIpccMsgReceiver::MsgReceivedFtor::MsgReceivedFtor(
        const MsgReceivedFtor&  other)
    : CheckFtorIF(),
      m_check_flag(other.m_check_flag)
    {
    }

    void TestIpccMsgReceiver::MsgReceivedFtor::reset()
    {
      m_check_flag = false;
    }

    void TestIpccMsgReceiver::MsgReceivedFtor::set()
    {
      m_check_flag = true;
    }

    bool TestIpccMsgReceiver::MsgReceivedFtor::do_check() const
    {
      return m_check_flag;
    }

    lmp::base::CheckFtorIF* TestIpccMsgReceiver::MsgReceivedFtor::do_clone() const
    {
      return new MsgReceivedFtor(*this);
    }

  } // namespace cc
} // namespace lmp
