/*
 * CCUnitTest.cpp
 *
 *  Created on: 27.02.2015
 *      Author: tom
 */

#include "base/CheckExpiryTimerFtor.hpp"
#include "base/CheckCompositeFtor.hpp"
#include "base/IntervalTimer.hpp"
#include "node/Node.hpp"
#include "neighbor/NeighborApplicationIF.hpp"
#include "cc/IPCC_Impl.hpp"
#include "cc/IPCC_NetIFSocket.hpp"
#include "cc/UDP_Msg_Handler.hpp"
#include "cc/IPCC_State.hpp"
#include "cc/IPCC_Event.hpp"
#include "cc/IPCC_Action.hpp"
#include "msg/ConfigAst.hpp"
#include "msg/ConfigAckAst.hpp"
#include "msg/ConfigNackAst.hpp"
#include "msg/HelloAst.hpp"
#include "msg/MessageParser.hpp"
#include "msg/MessageGenerator.hpp"
#include "Test_IPCC_Observer.hpp"
#include "Test_IPCC_Msg_Receiver.hpp"
#include "Test_NeighborDiscoveredCheckFtor.hpp"
#include "Test_EventCallbackCalledCheckFtor.hpp"
#include "Test_NoTimeoutScheduledCheckFtor.hpp"
#include "Test_Wait.hpp"

#include <boost/asio/io_service.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/object/static_cast.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/buffers_iterator.hpp>

#include <vector>

#define BOOST_TEST_MAIN
#if !defined( WIN32 )
    #define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

#define BOOST_TEST_MODULE LMP
// #include <BoostTestTargetConfig.h>
// #include <boost/test/included/unit_test.hpp>


// NetIFSocket <-> CCId
// NetIFSocket x sender_endpoint <-> IPCC

struct WrapFunc
{
  explicit WrapFunc(
    boost::function<void (void)>      callback)
  : m_callback(callback)
  {}
  bool operator()()
  {
    m_callback();
    return false;
  }
  boost::function<void (void)>      m_callback;
};

BOOST_AUTO_TEST_SUITE( lmp_socket )

BOOST_AUTO_TEST_CASE( retransmitTimer_retryLimit_singleThread )
{
  boost::asio::io_service io_service;
  std::chrono::milliseconds  initialRetransmitIinterval = std::chrono::milliseconds(50);
  lmp::DWORD   retryLimit = 3;
  lmp::DWORD   incrementValueDelta = 1;
  lmp::cc::test::EventCallbackCalledCheckFtor  eventCallbackCalledCheckFtor(retryLimit);
  lmp::base::RetransmitTimer
    retransmitTimer(io_service,
                    initialRetransmitIinterval,
                    retryLimit,
                    incrementValueDelta,
                    boost::function<bool (bool)>(boost::bind(&lmp::cc::test::EventCallbackCalledCheckFtor::eventOccurred,
                                                             &eventCallbackCalledCheckFtor,
                                                             _1)));
  std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
  retransmitTimer.start();
  BOOST_CHECK(lmp::test::util::wait(eventCallbackCalledCheckFtor, io_service, std::chrono::milliseconds(400)));
  {
    std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
    std::chrono::milliseconds timeout = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "RetransmitTimer retry limit reached: " << timeout.count() << std::endl;
  }
  BOOST_CHECK(eventCallbackCalledCheckFtor());
  {
    const lmp::cc::test::EventCallbackCalledCheckFtor::TimeoutEventSequence&  timeoutEventSequence =
      eventCallbackCalledCheckFtor.getTimeouts();
    //      Prior to initial transmission, initialize Rk = Ri and Rn = 0.
    std::chrono::milliseconds  currentRetransmitIinterval = initialRetransmitIinterval;
    std::chrono::steady_clock::time_point interval_start_time = start_time;
    lmp::DWORD                 retryCounter = 0;
    lmp::cc::test::EventCallbackCalledCheckFtor::TimeoutEventSequence::const_iterator toIter =
      timeoutEventSequence.begin();
    //
    //      while (Rn++ < Rl) {
    while (retryCounter++ < retryLimit)
    {
    //        transmit the message;
    //        wake up after Rk milliseconds;
      BOOST_CHECK(toIter != timeoutEventSequence.end());
      if (toIter != timeoutEventSequence.end())
      {
        const lmp::cc::test::EventCallbackCalledCheckFtor::TimeoutEvent& timeoutEvent = *toIter;
        std::chrono::milliseconds timeout =
          std::chrono::duration_cast<std::chrono::milliseconds>(timeoutEvent.timePoint - interval_start_time);
        BOOST_CHECK_EQUAL(timeout.count(), currentRetransmitIinterval.count());
        BOOST_CHECK_EQUAL(timeoutEvent.retryLimitReached, !(retryCounter < retryLimit));
        interval_start_time = timeoutEvent.timePoint;
        ++toIter;
      }
      currentRetransmitIinterval *= (1 + incrementValueDelta);
    //        Rk = Rk * (1 + Delta);
    }

  }
}

BOOST_AUTO_TEST_CASE( retransmitTimer_retryLimit )
{
  boost::asio::io_service io_service;
  boost::thread_group threadpool;
  boost::asio::io_service::work  work(io_service);
  threadpool.create_thread(boost::bind(&boost::asio::io_service::run, &io_service));
  //threadpool.create_thread(boost::bind(&boost::asio::io_service::run, &io_service));
  std::chrono::milliseconds  initialRetransmitIinterval = std::chrono::milliseconds(50);
  lmp::DWORD   retryLimit = 3;
  lmp::DWORD   incrementValueDelta = 1;
  lmp::cc::test::EventCallbackCalledCheckFtor  eventCallbackCalledCheckFtor(retryLimit);
  lmp::base::RetransmitTimer
    retransmitTimer(io_service,
                    initialRetransmitIinterval,
                    retryLimit,
                    incrementValueDelta,
                    boost::function<bool (bool)>(boost::bind(&lmp::cc::test::EventCallbackCalledCheckFtor::eventOccurred,
                                                             &eventCallbackCalledCheckFtor,
                                                             _1)));
  std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
  io_service.post(boost::bind(&lmp::base::RetransmitTimer::start,
                              &retransmitTimer));
  //retransmitTimer.start();
  BOOST_CHECK(lmp::test::util::wait(eventCallbackCalledCheckFtor, io_service, std::chrono::milliseconds(400)));
  {
    std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
    std::chrono::milliseconds timeout = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "RetransmitTimer retry limit reached: " << timeout.count() << std::endl;
  }
  BOOST_CHECK(eventCallbackCalledCheckFtor());
  {
    const lmp::cc::test::EventCallbackCalledCheckFtor::TimeoutEventSequence&  timeoutEventSequence =
      eventCallbackCalledCheckFtor.getTimeouts();
    //      Prior to initial transmission, initialize Rk = Ri and Rn = 0.
    std::chrono::milliseconds  currentRetransmitIinterval = initialRetransmitIinterval;
    std::chrono::steady_clock::time_point interval_start_time = start_time;
    lmp::DWORD                 retryCounter = 0;
    lmp::cc::test::EventCallbackCalledCheckFtor::TimeoutEventSequence::const_iterator toIter =
      timeoutEventSequence.begin();
    //
    //      while (Rn++ < Rl) {
    while (retryCounter++ < retryLimit)
    {
    //        transmit the message;
    //        wake up after Rk milliseconds;
      BOOST_CHECK(toIter != timeoutEventSequence.end());
      if (toIter != timeoutEventSequence.end())
      {
        const lmp::cc::test::EventCallbackCalledCheckFtor::TimeoutEvent& timeoutEvent = *toIter;
        std::chrono::milliseconds timeout =
          std::chrono::duration_cast<std::chrono::milliseconds>(timeoutEvent.timePoint - interval_start_time);
        BOOST_CHECK_EQUAL(timeout.count(), currentRetransmitIinterval.count());
        BOOST_CHECK_EQUAL(timeoutEvent.retryLimitReached, !(retryCounter < retryLimit));
        interval_start_time = timeoutEvent.timePoint;
        ++toIter;
      }
      currentRetransmitIinterval *= (1 + incrementValueDelta);
    //        Rk = Rk * (1 + Delta);
    }

  }

  io_service.stop();
  threadpool.join_all();
}

BOOST_AUTO_TEST_CASE( retransmitTimer_stop )
{
  boost::asio::io_service io_service;
  boost::thread_group threadpool;
  boost::asio::io_service::work  work(io_service);
  threadpool.create_thread(boost::bind(&boost::asio::io_service::run, &io_service));
  //threadpool.create_thread(boost::bind(&boost::asio::io_service::run, &io_service));
  std::chrono::milliseconds  initialRetransmitIinterval = std::chrono::milliseconds(50);
  lmp::DWORD   retryLimit = 3;
  lmp::DWORD   expectedRetries = 2;
  lmp::DWORD   incrementValueDelta = 1;
  lmp::cc::test::EventCallbackCalledCheckFtor  eventCallbackCalledCheckFtor(retryLimit);
  lmp::base::RetransmitTimer
    retransmitTimer(io_service,
                    initialRetransmitIinterval,
                    retryLimit,
                    incrementValueDelta,
                    boost::function<bool (bool)>(boost::bind(&lmp::cc::test::EventCallbackCalledCheckFtor::eventOccurred,
                                                             &eventCallbackCalledCheckFtor,
                                                             _1)));
  WrapFunc
    wrapFunc(boost::function<void (void)>(boost::bind(&lmp::base::RetransmitTimer::stop,
                                                      &retransmitTimer)));
  lmp::base::IntervalTimer
    intervalTimer(io_service,
                  std::chrono::milliseconds(170),
                  boost::function<bool (void)>(boost::ref(wrapFunc)));
  std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
  io_service.post(boost::bind(&lmp::base::IntervalTimer::start,
                              &intervalTimer));
  io_service.post(boost::bind(&lmp::base::RetransmitTimer::start,
                              &retransmitTimer));
  //retransmitTimer.start();
  lmp::cc::test::NoTimeoutScheduledCheckFtor  noTimeoutScheduledCheckFtor(retransmitTimer, eventCallbackCalledCheckFtor);
  lmp::base::CheckOrCompositeFtor  checkOrCompositeFtor(eventCallbackCalledCheckFtor, noTimeoutScheduledCheckFtor);
  BOOST_CHECK(lmp::test::util::wait(checkOrCompositeFtor, io_service, std::chrono::milliseconds(180)));
  {
    std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
    std::chrono::milliseconds timeout = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "test_RetransmitTimer 1st time-out: " << timeout.count() << std::endl;
  }
  BOOST_CHECK(!eventCallbackCalledCheckFtor());
  {
    const lmp::cc::test::EventCallbackCalledCheckFtor::TimeoutEventSequence&  timeoutEventSequence =
      eventCallbackCalledCheckFtor.getTimeouts();
    //      Prior to initial transmission, initialize Rk = Ri and Rn = 0.
    std::chrono::milliseconds  currentRetransmitIinterval = initialRetransmitIinterval;
    std::chrono::steady_clock::time_point interval_start_time = start_time;
    lmp::DWORD                 retryCounter = 0;
    lmp::cc::test::EventCallbackCalledCheckFtor::TimeoutEventSequence::const_iterator toIter =
      timeoutEventSequence.begin();
    //
    //      while (Rn++ < Rl) {
    while (retryCounter++ < expectedRetries)
    {
    //        transmit the message;
    //        wake up after Rk milliseconds;
      BOOST_CHECK(toIter != timeoutEventSequence.end());
      if (toIter != timeoutEventSequence.end())
      {
        const lmp::cc::test::EventCallbackCalledCheckFtor::TimeoutEvent& timeoutEvent = *toIter;
        std::chrono::milliseconds timeout =
          std::chrono::duration_cast<std::chrono::milliseconds>(timeoutEvent.timePoint - interval_start_time);
        BOOST_CHECK_EQUAL(timeout.count(), currentRetransmitIinterval.count());
        BOOST_CHECK_EQUAL(timeoutEvent.retryLimitReached, !(retryCounter < retryLimit));
        interval_start_time = timeoutEvent.timePoint;
        ++toIter;
      }
      currentRetransmitIinterval *= (1 + incrementValueDelta);
    //        Rk = Rk * (1 + Delta);
    }

  }

  io_service.stop();
  threadpool.join_all();
}


BOOST_AUTO_TEST_CASE( getIfAddress )
{
  {
    std::string ifName = "wlp1s0";
    lmp::cc::NetworkIFSocket::OptAddresses addr = lmp::cc::NetworkIFSocket::getIfAddress(ifName);
    BOOST_CHECK(addr.first);
    if (addr.first)
    {
      // std::cout << *addr.first << std::endl;
      BOOST_CHECK_EQUAL(*addr.first, boost::asio::ip::address::from_string("192.168.0.220"));
    }
    BOOST_CHECK(addr.second);
    if (addr.second)
    {
      std::cout << *addr.second << std::endl;
    }
  }
  {
    std::string ifName = "lo";
    lmp::cc::NetworkIFSocket::OptAddresses addr = lmp::cc::NetworkIFSocket::getIfAddress(ifName);
    BOOST_CHECK(addr.first);
    if (addr.first)
    {
      // std::cout << *addr.first << std::endl;
      BOOST_CHECK_EQUAL(*addr.first, boost::asio::ip::address::from_string("127.0.0.1"));
    }
    BOOST_CHECK(addr.second);
    if (addr.second)
    {
      // std::cout << *addr.second << std::endl;
      BOOST_CHECK_EQUAL(*addr.second, boost::asio::ip::address::from_string("::1"));
    }
  }
}

BOOST_AUTO_TEST_CASE( bind_socket_to_loopback_addr)
{
  boost::asio::io_service io_service;
  std::string ifName = "lo";
  lmp::cc::NetworkIFSocket::OptAddresses addr = lmp::cc::NetworkIFSocket::getIfAddress(ifName);
  BOOST_CHECK(addr.first);
  if (addr.first)
  {
    lmp::DWORD  node1_nodeId = 1;
    lmp::node::Node  node1(node1_nodeId);
    lmp::cc::UDPMsgHandler node1_MsgHandler(node1);
    unsigned short node1_port = 9701;
    boost::asio::ip::udp::endpoint node1_endpoint(*addr.first, node1_port);
    lmp::DWORD  node1_1stCCId = 1;
    // lmp::cc::TestIpccMsgReceiver node1_msgReceiver;
    lmp::cc::NetworkIFSocket  node1_lmpSocket(io_service, ifName, node1_port, node1_MsgHandler, false);
    node1_lmpSocket.enable();

    lmp::DWORD  node2_nodeId = 2;
    lmp::node::Node  node2(node2_nodeId);
    lmp::cc::UDPMsgHandler node2_MsgHandler(node2);
    unsigned short node2_port = 9702;
    boost::asio::ip::udp::endpoint node2_endpoint(*addr.first, node2_port);
    lmp::DWORD  node2_1stCCId = 1;
    // lmp::cc::TestIpccMsgReceiver node2_msgReceiver;
    lmp::cc::NetworkIFSocket  node2_lmpSocket(io_service, ifName, node2_port, node2_MsgHandler, false);
    node2_lmpSocket.enable();

    lmp::obj::config::ast::ConfigObjectSequence  configObjectSequence;
    {
      lmp::obj::config::ast::HelloConfig  helloConfig = { { true }, 0x009A, 0x01CF };
      configObjectSequence.push_back(lmp::obj::config::ast::ConfigCTypes(helloConfig));
    }
    lmp::msg::ast::Config  configMsg =
      { { false,
          false },
        { { false }, node1_1stCCId },      // localCCId
        { { false }, 0x1020508 },      // messageId
        { { false }, node2_nodeId },      // localNodeId
        configObjectSequence // configObjectss
      };
    lmp::msg::ast::Message sendMessage = configMsg;

    node2_MsgHandler.sendMessage(node2_lmpSocket, node1_endpoint, sendMessage);
//    node1_lmpSocket.send(node2_endpoint, sendBuffer);

    lmp::cc::test::NeighborDiscoveredCheckFtor  neighborDiscoveredCheckFtor(node1, node2_nodeId);
    BOOST_CHECK(lmp::test::util::wait(neighborDiscoveredCheckFtor, io_service, std::chrono::milliseconds(1000)));
    node1_lmpSocket.disable();
    node2_lmpSocket.disable();
    lmp::neighbor::NeighborApplicationIF const* neighbor = node1.getNeighbor(node2_nodeId);
    BOOST_CHECK(neighbor);
    BOOST_CHECK_EQUAL(neighbor->getNodeId(), node2_nodeId);
    lmp::cc::IpccMsgReceiveIF* ipccMsgRecIF = node1_MsgHandler.accessIpcc(node2_endpoint);
    BOOST_CHECK(ipccMsgRecIF);
    if (ipccMsgRecIF)
    {
      lmp::cc::IpccApplicationIF* ipccPtr =
        dynamic_cast<lmp::cc::IpccApplicationIF*>(ipccMsgRecIF);
      if (ipccPtr)
      {
        ipccPtr->disable();
        node1.neighborAdjacencyRemoved(node2_nodeId, *ipccPtr);
      }
      node1_MsgHandler.removeIpcc(node2_endpoint);
    }
    //io_service.run_one();
    //io_service.run_one();
  }
}

BOOST_AUTO_TEST_CASE( bind_socket_to_netif)
{
  unsigned short port = 9701;
  std::string ifName = "virbr0";
  lmp::node::Node  node1(1);
  lmp::cc::UDPMsgHandler node1_MsgHandler(node1);
  lmp::DWORD  node1_1stCCId = 1;

  boost::asio::io_service io_service;
  // lmp::cc::IpccImpl  activeIPCC(123, port, true);
  lmp::cc::NetworkIFSocket  lmpSocket(io_service, ifName, port, node1_MsgHandler, true);

  boost::asio::ip::udp::endpoint remote_endpoint(boost::asio::ip::address::from_string("224.0.0.1"),
                                                 port);
  lmp::obj::config::ast::ConfigObjectSequence  configObjectSequence;
  {
    lmp::obj::config::ast::HelloConfig  helloConfig = { { true }, 0x009A, 0x01CF };
    configObjectSequence.push_back(lmp::obj::config::ast::ConfigCTypes(helloConfig));
  }
  lmp::msg::ast::Config  configMsg =
    { { false,
        false },
      { { false }, 0x1020008 },      // localCCId
      { { false }, 0x1020508 },      // messageId
      { { false }, 0x8600420 },      // localNodeId
        configObjectSequence  // configObjectss
    };
  const lmp::WORD msgLength = lmp::msg::ast::getLength(configMsg);
  unsigned char rawBuffer[msgLength];
  boost::asio::mutable_buffers_1 sendBuffer(rawBuffer, msgLength);
  typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
  BufOutIterType  gen_begin = boost::asio::buffers_begin(sendBuffer);
  BufOutIterType gen_last = boost::asio::buffers_end(sendBuffer);
  using boost::spirit::karma::generate;
  lmp::msg::generator::message_grammar<BufOutIterType>  configMsgGenerateGrammar;
  BOOST_CHECK(generate(gen_begin,
                       configMsgGenerateGrammar,
                       configMsg));

  lmpSocket.send(remote_endpoint, sendBuffer);
}

BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE( lmp_ipcc_active )

BOOST_AUTO_TEST_CASE( activeIPCC_CCDown )
{
  boost::asio::io_service io_service;
  std::string ifName = "lo";
  lmp::cc::NetworkIFSocket::OptAddresses addr =
    lmp::cc::NetworkIFSocket::getIfAddress(ifName);
  BOOST_CHECK(addr.first);
  if (addr.first)
  {
    lmp::DWORD  node1_nodeId = 1;
    lmp::node::Node  node1(node1_nodeId);
    lmp::cc::UDPMsgHandler node1_MsgHandler(node1);
    unsigned short node1_port = 9701;
    boost::asio::ip::udp::endpoint node1_endpoint(*addr.first, node1_port);
    lmp::DWORD  node1_1stCCId = 1;
    lmp::cc::NetworkIFSocket  node1_lmpSocket(io_service, ifName, node1_port, node1_MsgHandler, false);
    unsigned short node2_port = 9702;
    boost::asio::ip::udp::endpoint node2_endpoint(*addr.first, node2_port);
    lmp::cc::IpccImpl  activeIPCC(node1_1stCCId, node1, node1_lmpSocket, io_service, node2_endpoint, true);
    lmp::cc::appl::TestIpccObserver  ipccObserver(activeIPCC);
    activeIPCC.enable();
    {
      lmp::cc::appl::TestIpccObserver::TransistionSequence expectedTransitions;
      expectedTransitions.push_back(lmp::cc::appl::TestIpccObserver::TransRecord(lmp::cc::appl::State::Down,
                                                                                 lmp::cc::appl::Event::EvBringUp,
                                                                                 lmp::cc::appl::State::ConfSnd,
                                                                                 lmp::cc::appl::Action::ActionSendConfig));
      BOOST_CHECK_EQUAL(ipccObserver.getTransistions(), expectedTransitions);
      ipccObserver.reset();
      const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getState();
      BOOST_CHECK(activeState);
      if (activeState)
      {
        BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::ConfSnd());
      }
    }
    activeIPCC.evtCCDown();
    {
      lmp::cc::appl::TestIpccObserver::TransistionSequence expectedTransitions;
      expectedTransitions.push_back(lmp::cc::appl::TestIpccObserver::TransRecord(lmp::cc::appl::State::ConfSnd,
                                                                                 lmp::cc::appl::Event::EvCCDn,
                                                                                 lmp::cc::appl::State::Down,
                                                                                 lmp::cc::appl::Action::ActionStopSendConfig));
      BOOST_CHECK_EQUAL(ipccObserver.getTransistions(), expectedTransitions);
      const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getState();
      BOOST_CHECK(activeState);
      if (activeState)
      {
        BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::Down());
      }
    }
  }
}

BOOST_AUTO_TEST_CASE( activeIPCC_AdminDown )
{
  boost::asio::io_service io_service;
  std::string ifName = "lo";
  lmp::cc::NetworkIFSocket::OptAddresses addr =
    lmp::cc::NetworkIFSocket::getIfAddress(ifName);
  BOOST_CHECK(addr.first);
  if (addr.first)
  {
    lmp::DWORD  node1_nodeId = 1;
    lmp::node::Node  node1(node1_nodeId);
    lmp::cc::UDPMsgHandler node1_MsgHandler(node1);
    unsigned short node1_port = 9701;
    boost::asio::ip::udp::endpoint node1_endpoint(*addr.first, node1_port);
    lmp::DWORD  node1_1stCCId = 1;
    lmp::cc::NetworkIFSocket  node1_lmpSocket(io_service, ifName, node1_port, node1_MsgHandler, false);
    unsigned short node2_port = 9702;
    boost::asio::ip::udp::endpoint node2_endpoint(*addr.first, node2_port);
    lmp::cc::IpccImpl  activeIPCC(node1_1stCCId, node1, node1_lmpSocket, io_service, node2_endpoint, true);
    lmp::cc::appl::TestIpccObserver  ipccObserver(activeIPCC);
    activeIPCC.enable();
    {
      const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getState();
      BOOST_CHECK(activeState);
      if (activeState)
      {
        BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::ConfSnd());
      }
    }
    activeIPCC.disable();
    {
      const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getState();
      BOOST_CHECK(activeState);
      if (activeState)
      {
        BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::Down());
      }
    }
  }
}

BOOST_AUTO_TEST_CASE( activeIPCC_ConfigErr )
{
  boost::asio::io_service io_service;
  std::string ifName = "lo";
  lmp::cc::NetworkIFSocket::OptAddresses addr = lmp::cc::NetworkIFSocket::getIfAddress(ifName);
  BOOST_CHECK(addr.first);
  if (addr.first)
  {
    lmp::DWORD  node1_nodeId = 1;
    lmp::node::Node  node1(node1_nodeId);
    lmp::cc::UDPMsgHandler node1_MsgHandler(node1);
    unsigned short node1_port = 9701;
    boost::asio::ip::udp::endpoint node1_endpoint(*addr.first, node1_port);
    lmp::DWORD  node1_1stCCId = 1;
    lmp::cc::NetworkIFSocket  node1_lmpSocket(io_service, ifName, node1_port, node1_MsgHandler, false);
    unsigned short node2_port = 9702;
    boost::asio::ip::udp::endpoint node2_endpoint(*addr.first, node2_port);
    lmp::cc::IpccImpl  activeIPCC(node1_1stCCId, node1, node1_lmpSocket, io_service, node2_endpoint, true);
    lmp::cc::appl::TestIpccObserver  ipccObserver(activeIPCC);
    activeIPCC.enable();
    {
      lmp::cc::appl::TestIpccObserver::TransistionSequence expectedTransitions;
      expectedTransitions.push_back(lmp::cc::appl::TestIpccObserver::TransRecord(lmp::cc::appl::State::Down,
                                                                                 lmp::cc::appl::Event::EvBringUp,
                                                                                 lmp::cc::appl::State::ConfSnd,
                                                                                 lmp::cc::appl::Action::ActionSendConfig));
      BOOST_CHECK_EQUAL(ipccObserver.getTransistions(), expectedTransitions);
      ipccObserver.reset();
      const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getState();
      BOOST_CHECK(activeState);
      if (activeState)
      {
        BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::ConfSnd());
      }
    }
    lmp::msg::ast::ConfigNack configNackMsg =
      { { false,
          false },
        { { false }, 2 },        // localCCId
        { { false }, 115 },      // localNodeId
        { { false }, 7 },        // remoteCCId
        { { false }, 34 },       // messageId
        { { false }, 117 },      // remoteNodeId
        { { true }, 100, 450 } // helloConfig
      };
    activeIPCC.processReceivedMessage(configNackMsg);
    {
      const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getState();
      BOOST_CHECK(activeState);
      if (activeState)
      {
        BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::ConfSnd());
      }
    }
    activeIPCC.disable();
    {
      const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getState();
      BOOST_CHECK(activeState);
      if (activeState)
      {
        BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::Down());
      }
    }
  }
}

BOOST_AUTO_TEST_CASE( activeIPCC_ContenWin )
{
  boost::asio::io_service io_service;
  std::string ifName = "lo";
  lmp::cc::NetworkIFSocket::OptAddresses addr = lmp::cc::NetworkIFSocket::getIfAddress(ifName);
  BOOST_CHECK(addr.first);
  if (addr.first)
  {
    lmp::DWORD  node1_nodeId = 123;
    lmp::node::Node  node1(node1_nodeId);
    lmp::cc::UDPMsgHandler node1_MsgHandler(node1);
    unsigned short node1_port = 9701;
    boost::asio::ip::udp::endpoint node1_endpoint(*addr.first, node1_port);
    lmp::DWORD  node1_1stCCId = 7001;
    lmp::cc::NetworkIFSocket  node1_lmpSocket(io_service, ifName, node1_port, node1_MsgHandler, false);
    lmp::DWORD  node2_nodeId = 115;
    unsigned short node2_port = 9702;
    lmp::DWORD  node2_1stCCId = 7002;
    boost::asio::ip::udp::endpoint node2_endpoint(*addr.first, node2_port);
    lmp::cc::IpccImpl  activeIPCC(node1_1stCCId, node1, node1_lmpSocket, io_service, node2_endpoint, true);
    lmp::cc::appl::TestIpccObserver  ipccObserver(activeIPCC);
    activeIPCC.enable();
    {
      lmp::cc::appl::TestIpccObserver::TransistionSequence expectedTransitions;
      expectedTransitions.push_back(lmp::cc::appl::TestIpccObserver::TransRecord(lmp::cc::appl::State::Down,
                                                                                 lmp::cc::appl::Event::EvBringUp,
                                                                                 lmp::cc::appl::State::ConfSnd,
                                                                                 lmp::cc::appl::Action::ActionSendConfig));
      BOOST_CHECK_EQUAL(ipccObserver.getTransistions(), expectedTransitions);
      ipccObserver.reset();
      const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getState();
      BOOST_CHECK(activeState);
      if (activeState)
      {
        BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::ConfSnd());
      }
    }
    lmp::obj::config::ast::ConfigObjectSequence  configObjectSequence;
    {
      lmp::obj::config::ast::HelloConfig  helloConfig = { { true }, 100, 450 };// helloConfig
      configObjectSequence.push_back(lmp::obj::config::ast::ConfigCTypes(helloConfig));
    }
    lmp::msg::ast::Config  configMsg =
      { { false,
          false },
        { { false }, node2_1stCCId },      // localCCId
        { { false }, 34 },     // messageId
        { { false }, node2_nodeId },    // localNodeId
          configObjectSequence  // configObjects
      };

    activeIPCC.processReceivedMessage(configMsg);
    {
      const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getState();
      BOOST_CHECK(activeState);
      if (activeState)
      {
        BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::ConfSnd());
      }
    }
    activeIPCC.disable();
    {
      const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getState();
      BOOST_CHECK(activeState);
      if (activeState)
      {
        BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::Down());
      }
    }
  }
}

BOOST_AUTO_TEST_CASE( activeIPCC_Reconfig )
{
  boost::asio::io_service io_service;
  std::string ifName = "lo";
  lmp::cc::NetworkIFSocket::OptAddresses addr = lmp::cc::NetworkIFSocket::getIfAddress(ifName);
  BOOST_CHECK(addr.first);
  if (addr.first)
  {
    lmp::DWORD  node1_nodeId = 123;
    lmp::node::Node  node1(node1_nodeId);
    lmp::cc::UDPMsgHandler node1_MsgHandler(node1);
    unsigned short node1_port = 9701;
    boost::asio::ip::udp::endpoint node1_endpoint(*addr.first, node1_port);
    lmp::DWORD  node1_1stCCId = 7001;
    lmp::cc::NetworkIFSocket  node1_lmpSocket(io_service, ifName, node1_port, node1_MsgHandler, false);
    lmp::DWORD  node2_nodeId = 115;
    unsigned short node2_port = 9702;
    lmp::DWORD  node2_1stCCId = 7002;
    boost::asio::ip::udp::endpoint node2_endpoint(*addr.first, node2_port);
    lmp::cc::IpccImpl  activeIPCC(node1_1stCCId, node1, node1_lmpSocket, io_service, node2_endpoint, true);
    lmp::cc::appl::TestIpccObserver  ipccObserver(activeIPCC);
    activeIPCC.enable();
    {
      lmp::cc::appl::TestIpccObserver::TransistionSequence expectedTransitions;
      expectedTransitions.push_back(lmp::cc::appl::TestIpccObserver::TransRecord(lmp::cc::appl::State::Down,
                                                                                 lmp::cc::appl::Event::EvBringUp,
                                                                                 lmp::cc::appl::State::ConfSnd,
                                                                                 lmp::cc::appl::Action::ActionSendConfig));
      BOOST_CHECK_EQUAL(ipccObserver.getTransistions(), expectedTransitions);
      ipccObserver.reset();
      const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getState();
      BOOST_CHECK(activeState);
      if (activeState)
      {
        BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::ConfSnd());
      }
    }
    lmp::obj::config::ast::HelloConfig  helloConfig = { { true }, 150, 600 };
    activeIPCC.reconfigure(helloConfig);
    {
      const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getState();
      BOOST_CHECK(activeState);
      if (activeState)
      {
        BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::ConfSnd());
      }
    }
    activeIPCC.disable();
  }
}

BOOST_AUTO_TEST_CASE( activeIPCC_ConfRet )
{
  boost::asio::io_service io_service;
  std::string ifName = "lo";
  lmp::cc::NetworkIFSocket::OptAddresses addr = lmp::cc::NetworkIFSocket::getIfAddress(ifName);
  BOOST_CHECK(addr.first);
  if (addr.first)
  {
    lmp::DWORD  node1_nodeId = 123;
    lmp::node::Node  node1(node1_nodeId);
    lmp::cc::UDPMsgHandler node1_MsgHandler(node1);
    unsigned short node1_port = 9701;
    boost::asio::ip::udp::endpoint node1_endpoint(*addr.first, node1_port);
    lmp::DWORD  node1_1stCCId = 7001;
    lmp::cc::NetworkIFSocket  node1_lmpSocket(io_service, ifName, node1_port, node1_MsgHandler, false);
    lmp::DWORD  node2_nodeId = 115;
    unsigned short node2_port = 9702;
    lmp::DWORD  node2_1stCCId = 7002;
    boost::asio::ip::udp::endpoint node2_endpoint(*addr.first, node2_port);
    lmp::cc::IpccImpl  activeIPCC(node1_1stCCId, node1, node1_lmpSocket, io_service, node2_endpoint, true);
    lmp::cc::appl::TestIpccObserver  ipccObserver(activeIPCC);
    activeIPCC.enable();
    {
      lmp::cc::appl::TestIpccObserver::TransistionSequence expectedTransitions;
      expectedTransitions.push_back(lmp::cc::appl::TestIpccObserver::TransRecord(lmp::cc::appl::State::Down,
                                                                                 lmp::cc::appl::Event::EvBringUp,
                                                                                 lmp::cc::appl::State::ConfSnd,
                                                                                 lmp::cc::appl::Action::ActionSendConfig));
      BOOST_CHECK_EQUAL(ipccObserver.getTransistions(), expectedTransitions);
      ipccObserver.reset();
      const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getState();
      BOOST_CHECK(activeState);
      if (activeState)
      {
        BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::ConfSnd());
      }
    }
    activeIPCC.evtConfRet(false);
    {
      const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getState();
      BOOST_CHECK(activeState);
      if (activeState)
      {
        BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::ConfSnd());
      }
    }
    activeIPCC.disable();
  }
}

BOOST_AUTO_TEST_CASE( activeIPCC_ContenLost_NotAcceptConf )
{
  boost::asio::io_service io_service;
  std::string ifName = "lo";
  lmp::cc::NetworkIFSocket::OptAddresses addr = lmp::cc::NetworkIFSocket::getIfAddress(ifName);
  BOOST_CHECK(addr.first);
  if (addr.first)
  {
    lmp::DWORD  node1_nodeId = 123;
    lmp::node::Node  node1(node1_nodeId);
    lmp::cc::UDPMsgHandler node1_MsgHandler(node1);
    unsigned short node1_port = 9701;
    boost::asio::ip::udp::endpoint node1_endpoint(*addr.first, node1_port);
    lmp::DWORD  node1_1stCCId = 7001;
    lmp::cc::NetworkIFSocket  node1_lmpSocket(io_service, ifName, node1_port, node1_MsgHandler, false);
    lmp::DWORD  node2_nodeId = 128;
    unsigned short node2_port = 9702;
    lmp::DWORD  node2_1stCCId = 7002;
    boost::asio::ip::udp::endpoint node2_endpoint(*addr.first, node2_port);
    lmp::cc::IpccImpl  activeIPCC(node1_1stCCId, node1, node1_lmpSocket, io_service, node2_endpoint, true);
    lmp::cc::appl::TestIpccObserver  ipccObserver(activeIPCC);
    activeIPCC.enable();
    {
      lmp::cc::appl::TestIpccObserver::TransistionSequence expectedTransitions;
      expectedTransitions.push_back(lmp::cc::appl::TestIpccObserver::TransRecord(lmp::cc::appl::State::Down,
                                                                                 lmp::cc::appl::Event::EvBringUp,
                                                                                 lmp::cc::appl::State::ConfSnd,
                                                                                 lmp::cc::appl::Action::ActionSendConfig));
      BOOST_CHECK_EQUAL(ipccObserver.getTransistions(), expectedTransitions);
      ipccObserver.reset();
      const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getState();
      BOOST_CHECK(activeState);
      if (activeState)
      {
        BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::ConfSnd());
      }
    }
    lmp::obj::config::ast::ConfigObjectSequence  configObjectSequence;
    {
      lmp::obj::config::ast::HelloConfig  helloConfig = { { true }, 450, 450 };// helloConfig
      configObjectSequence.push_back(lmp::obj::config::ast::ConfigCTypes(helloConfig));
    }
    lmp::msg::ast::Config  configMsg =
      { { false,
          false },
        { { false }, node2_1stCCId },      // localCCId
        { { false }, 34 },     // messageId
        { { false }, node2_nodeId },    // localNodeId
        configObjectSequence  // configObjectss
      };
    activeIPCC.processReceivedMessage(configMsg);
    // BOOST_TEST_MESSAGE("getState");
    {
      const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getState();
      BOOST_CHECK(activeState);
      if (activeState)
      {
        BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::ConfRcv());
      }
    }
    activeIPCC.disable();
    {
      const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getState();
      BOOST_CHECK(activeState);
      if (activeState)
      {
        BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::Down());
      }
    }
  }
}

BOOST_AUTO_TEST_CASE( activeIPCC_ConfDone_HelloRcvd )
{
  boost::asio::io_service io_service;
  std::string ifName = "lo";
  lmp::cc::NetworkIFSocket::OptAddresses addr = lmp::cc::NetworkIFSocket::getIfAddress(ifName);
  BOOST_CHECK(addr.first);
  if (addr.first)
  {
    lmp::DWORD  node1_nodeId = 123;
    lmp::node::Node  node1(node1_nodeId);
    lmp::cc::UDPMsgHandler node1_MsgHandler(node1);
    unsigned short node1_port = 9701;
    boost::asio::ip::udp::endpoint node1_endpoint(*addr.first, node1_port);
    lmp::DWORD  node1_1stCCId = 7001;
    lmp::cc::NetworkIFSocket  node1_lmpSocket(io_service, ifName, node1_port, node1_MsgHandler, false);
    lmp::DWORD  node2_nodeId = 115;
    unsigned short node2_port = 9702;
    lmp::DWORD  node2_1stCCId = 7002;
    boost::asio::ip::udp::endpoint node2_endpoint(*addr.first, node2_port);
    lmp::cc::IpccImpl  activeIPCC(node1_1stCCId, node1, node1_lmpSocket, io_service, node2_endpoint, true);
    lmp::cc::appl::TestIpccObserver  ipccObserver(activeIPCC);
    activeIPCC.enable();
    {
      lmp::cc::appl::TestIpccObserver::TransistionSequence expectedTransitions;
      expectedTransitions.push_back(lmp::cc::appl::TestIpccObserver::TransRecord(lmp::cc::appl::State::Down,
                                                                                 lmp::cc::appl::Event::EvBringUp,
                                                                                 lmp::cc::appl::State::ConfSnd,
                                                                                 lmp::cc::appl::Action::ActionSendConfig));
      BOOST_CHECK_EQUAL(ipccObserver.getTransistions(), expectedTransitions);
      ipccObserver.reset();
      const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getState();
      BOOST_CHECK(activeState);
      if (activeState)
      {
        BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::ConfSnd());
      }
    }
    lmp::msg::ast::ConfigAck configAckMsg =
      { { false,
          false },
        { { false }, node2_1stCCId },      // localCCId
        { { false }, node2_nodeId },    // localNodeId
        { { false }, node1_1stCCId },      // remoteCCId
        { { false }, 34 },     // messageId
        { { false }, node1_nodeId }   // remoteNodeId
      };
    activeIPCC.processReceivedMessage(configAckMsg);
    {
      lmp::cc::appl::TestIpccObserver::TransistionSequence expectedTransitions;
      expectedTransitions.push_back(lmp::cc::appl::TestIpccObserver::TransRecord(lmp::cc::appl::State::ConfSnd,
                                                                                 lmp::cc::appl::Event::EvConfDone,
                                                                                 lmp::cc::appl::State::Active,
                                                                                 lmp::cc::appl::Action::ActionStopSendConfig));
      expectedTransitions.push_back(lmp::cc::appl::TestIpccObserver::TransRecord(lmp::cc::appl::State::ConfSnd,
                                                                                 lmp::cc::appl::Event::EvConfDone,
                                                                                 lmp::cc::appl::State::Active,
                                                                                 lmp::cc::appl::Action::ActionSendHello));
      BOOST_CHECK_EQUAL(ipccObserver.getTransistions(), expectedTransitions);
      ipccObserver.reset();
      const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getState();
      BOOST_CHECK(activeState);
      if (activeState)
      {
        BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::Active());
      }
    }
    {
      lmp::msg::ast::Hello  helloMsg =
        { { false,
            false },
          { { false }, 1, 0 }    // hello
        };
      activeIPCC.processReceivedMessage(helloMsg);
      {
        lmp::cc::appl::TestIpccObserver::TransistionSequence expectedTransitions;
        expectedTransitions.push_back(lmp::cc::appl::TestIpccObserver::TransRecord(lmp::cc::appl::State::Active,
                                                                                 lmp::cc::appl::Event::EvSeqNumErr,
                                                                                 lmp::cc::appl::State::Active,
                                                                                 lmp::cc::appl::Action::ActionNoAction));
        BOOST_CHECK_EQUAL(ipccObserver.getTransistions(), expectedTransitions);
        ipccObserver.reset();
        const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getState();
        BOOST_CHECK(activeState);
        if (activeState)
        {
          BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::Active());
        }
      }
    }
    {
      lmp::msg::ast::Hello  helloMsg =
        { { false,
            false },
          { { false }, 1, 1 }     // hello
        };
      activeIPCC.processReceivedMessage(helloMsg);
      {
        lmp::cc::appl::TestIpccObserver::TransistionSequence expectedTransitions;
        expectedTransitions.push_back(lmp::cc::appl::TestIpccObserver::TransRecord(lmp::cc::appl::State::Active,
                                                                                   lmp::cc::appl::Event::EvHelloRcvd,
                                                                                   lmp::cc::appl::State::Up,
                                                                                   lmp::cc::appl::Action::ActionNoAction));
        BOOST_CHECK_EQUAL(ipccObserver.getTransistions(), expectedTransitions);
        ipccObserver.reset();
        const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getState();
        BOOST_CHECK(activeState);
        if (activeState)
        {
          BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::Up());
        }
      }
    }
    activeIPCC.evtHelloRet();
    {
      lmp::cc::appl::TestIpccObserver::TransistionSequence expectedTransitions;
      expectedTransitions.push_back(lmp::cc::appl::TestIpccObserver::TransRecord(lmp::cc::appl::State::Up,
                                                                                 lmp::cc::appl::Event::EvHelloRet,
                                                                                 lmp::cc::appl::State::Up,
                                                                                 lmp::cc::appl::Action::ActionSendHello));
      BOOST_CHECK_EQUAL(ipccObserver.getTransistions(), expectedTransitions);
      ipccObserver.reset();
      const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getState();
      BOOST_CHECK(activeState);
      if (activeState)
      {
        BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::Up());
      }
    }
    {
      lmp::msg::ast::Hello  helloMsg =
        { { false,
            false },
          { { false }, 2, 2 }   // hello
        };
      activeIPCC.processReceivedMessage(helloMsg);
      {
        lmp::cc::appl::TestIpccObserver::TransistionSequence expectedTransitions;
        expectedTransitions.push_back(lmp::cc::appl::TestIpccObserver::TransRecord(lmp::cc::appl::State::Up,
                                                                                   lmp::cc::appl::Event::EvHelloRcvd,
                                                                                   lmp::cc::appl::State::Up,
                                                                                   lmp::cc::appl::Action::ActionNoAction));
        BOOST_CHECK_EQUAL(ipccObserver.getTransistions(), expectedTransitions);
        ipccObserver.reset();
        const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getState();
        BOOST_CHECK(activeState);
        if (activeState)
        {
          BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::Up());
        }
      }
    }
    activeIPCC.disable();
    {
      lmp::cc::appl::TestIpccObserver::TransistionSequence expectedTransitions;
      expectedTransitions.push_back(lmp::cc::appl::TestIpccObserver::TransRecord(lmp::cc::appl::State::Up,
                                                                                 lmp::cc::appl::Event::EvAdminDown,
                                                                                 lmp::cc::appl::State::GoingDown,
                                                                                 lmp::cc::appl::Action::ActionSetCCDownFlag));
      BOOST_CHECK_EQUAL(ipccObserver.getTransistions(), expectedTransitions);
      ipccObserver.reset();
      const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getState();
      BOOST_CHECK(activeState);
      if (activeState)
      {
        BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::GoingDown());
      }
    }
    activeIPCC.evtDownTimer();
    {
      lmp::cc::appl::TestIpccObserver::TransistionSequence expectedTransitions;
      expectedTransitions.push_back(lmp::cc::appl::TestIpccObserver::TransRecord(lmp::cc::appl::State::GoingDown,
                                                                                 lmp::cc::appl::Event::EvDownTimer,
                                                                                 lmp::cc::appl::State::Down,
                                                                                 lmp::cc::appl::Action::ActionStopSendHello));
      BOOST_CHECK_EQUAL(ipccObserver.getTransistions(), expectedTransitions);
      ipccObserver.reset();
      const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getState();
      BOOST_CHECK(activeState);
      if (activeState)
      {
        BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::Down());
      }
    }
  }
}


BOOST_AUTO_TEST_CASE( activeIPCC_ContenLost_AcceptConf )
{
  boost::asio::io_service io_service;
  std::string ifName = "lo";
  lmp::cc::NetworkIFSocket::OptAddresses addr = lmp::cc::NetworkIFSocket::getIfAddress(ifName);
  BOOST_CHECK(addr.first);
  if (addr.first)
  {
    lmp::DWORD  node1_nodeId = 123;
    lmp::node::Node  node1(node1_nodeId);
    lmp::cc::UDPMsgHandler node1_MsgHandler(node1);
    unsigned short node1_port = 9701;
    boost::asio::ip::udp::endpoint node1_endpoint(*addr.first, node1_port);
    lmp::DWORD  node1_1stCCId = 7001;
    lmp::cc::NetworkIFSocket  node1_lmpSocket(io_service, ifName, node1_port, node1_MsgHandler, false);
    lmp::DWORD  node2_nodeId = 128;
    unsigned short node2_port = 9702;
    lmp::DWORD  node2_1stCCId = 7002;
    boost::asio::ip::udp::endpoint node2_endpoint(*addr.first, node2_port);
    lmp::cc::IpccImpl  activeIPCC(node1_1stCCId, node1, node1_lmpSocket, io_service, node2_endpoint, true);
    lmp::cc::appl::TestIpccObserver  ipccObserver(activeIPCC);
    activeIPCC.enable();
    {
      const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getState();
      BOOST_CHECK(activeState);
      if (activeState)
      {
        BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::ConfSnd());
      }
    }
    lmp::obj::config::ast::ConfigObjectSequence  configObjectSequence;
    {
      lmp::obj::config::ast::HelloConfig  helloConfig = { { true }, 100, 450 };// helloConfig
      configObjectSequence.push_back(lmp::obj::config::ast::ConfigCTypes(helloConfig));
    }
    lmp::msg::ast::Config  configMsg =
      { { false,
          false },
        { { false }, 7002 },      // localCCId
        { { false }, 32 },     // messageId
        { { false }, node2_nodeId },    // localNodeId
          configObjectSequence // configObjectss
      };
    activeIPCC.processReceivedMessage(configMsg);
    // BOOST_TEST_MESSAGE("getState");
    {
      const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getState();
      BOOST_CHECK(activeState);
      if (activeState)
      {
        BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::Active());
      }
    }
    activeIPCC.disable();
    {
      const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getState();
      BOOST_CHECK(activeState);
      if (activeState)
      {
        BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::GoingDown());
      }
    }
    activeIPCC.evtDownTimer();
    {
      const boost::optional<const lmp::cc::appl::State&>& activeState = activeIPCC.getState();
      BOOST_CHECK(activeState);
      if (activeState)
      {
        BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::Down());
      }
    }
  }
}


BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( lmp_ipcc_passive )

BOOST_AUTO_TEST_CASE( passiveIPCC )
{
  boost::asio::io_service io_service;
  std::string ifName = "lo";
  lmp::cc::NetworkIFSocket::OptAddresses addr = lmp::cc::NetworkIFSocket::getIfAddress(ifName);
  BOOST_CHECK(addr.first);
  if (addr.first)
  {
    lmp::DWORD  node1_nodeId = 123;
    lmp::node::Node  node1(node1_nodeId);
    lmp::cc::UDPMsgHandler node1_MsgHandler(node1);
    unsigned short node1_port = 9701;
    boost::asio::ip::udp::endpoint node1_endpoint(*addr.first, node1_port);
    lmp::DWORD  node1_1stCCId = 7001;
    lmp::cc::NetworkIFSocket  node1_lmpSocket(io_service, ifName, node1_port, node1_MsgHandler, false);
    lmp::DWORD  node2_nodeId = 128;
    unsigned short node2_port = 9702;
    lmp::DWORD  node2_1stCCId = 7002;
    boost::asio::ip::udp::endpoint node2_endpoint(*addr.first, node2_port);
    lmp::cc::IpccImpl  passiveIPCC(node1_1stCCId, node1, node1_lmpSocket, io_service, node2_endpoint, false);
    lmp::cc::appl::TestIpccObserver  ipccObserver(passiveIPCC);
    passiveIPCC.enable();
    {
      const boost::optional<const lmp::cc::appl::State&>& activeState = passiveIPCC.getState();
      BOOST_CHECK(activeState);
      if (activeState)
      {
        BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::ConfRcv());
      }
    }
    lmp::obj::config::ast::ConfigObjectSequence  configObjectSequence;
    {
      lmp::obj::config::ast::HelloConfig  helloConfig = { { true }, 100, 450 };// helloConfig
      configObjectSequence.push_back(lmp::obj::config::ast::ConfigCTypes(helloConfig));
    }
    lmp::msg::ast::Config  configMsg =
      { { false,
          false },
        { { false }, node2_1stCCId },      // localCCId
        { { false }, 38 },     // messageId
        { { false }, node2_nodeId },    // localNodeId
        configObjectSequence  // configObjectss
      };
    passiveIPCC.processReceivedMessage(configMsg);
    {
      const boost::optional<const lmp::cc::appl::State&>& activeState = passiveIPCC.getState();
      BOOST_CHECK(activeState);
      if (activeState)
      {
        BOOST_CHECK_EQUAL(*activeState, lmp::cc::appl::Active());
      }
    }
    passiveIPCC.disable();
  }
}

BOOST_AUTO_TEST_SUITE_END()
