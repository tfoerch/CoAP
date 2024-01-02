/*
 * IPCC_Impl.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "IPCC_Impl.hpp"
#include "node/NodeApplicationIF.hpp"
#include "NetworkIFSocketIF.hpp"
#include "IPCC_ObserverIF.hpp"
#include "IPCC_State.hpp"
#include "IPCC_Action.hpp"
#include "UDP_Msg_Handler.hpp"
#include "neighbor/NeighborAdjacencyObserverIF.hpp"
#include "msg/ConfigAst.hpp"
#include "msg/ConfigAckAst.hpp"
#include "msg/ConfigNackAst.hpp"
#include "msg/HelloAst.hpp"
#include "msg/MessageAst.hpp"

#include <boost/core/explicit_operator_bool.hpp>
#include <boost/ptr_container/detail/reversible_ptr_container.hpp>
#include <boost/ptr_container/detail/void_ptr_iterator.hpp>
#include <boost/bind.hpp>
#include <deque>
#include <limits>
#include <ostream>

namespace
{
  struct ConfigCTypes_IsAcceptableVisitor : boost::static_visitor<bool>
  {
    bool operator()(const lmp::obj::config::ast::HelloConfig& helloConfig) const
    {
      return
        ( (3 * helloConfig.m_helloIntv ) < helloConfig.m_helloDeadIntv );
    }
    bool operator()(const lmp::obj::config::ast::UnknownConfigCType& unknownConfig) const
    {
      return false;
    }
  };
}

namespace lmp
{
  namespace cc
  {
    IpccImpl::IpccImpl(
      lmp::DWORD                             localCCId,
      node::NodeApplicationIF&               node,
      NetworkIFSocketIF&                     networkIFSocket,
      boost::asio::io_context&               io_context,
      const boost::asio::ip::udp::endpoint&  remote_endpoint,
      bool                                   isActiveSetup)
      : m_localCCId(localCCId),
        m_node(node),
        m_networkIFSocket(networkIFSocket),
        m_io_context(io_context),
        m_remote_endpoint(remote_endpoint),
        m_remoteNodeId(0),
        m_remoteCCId(0),
        m_isActiveSetup(isActiveSetup),
        m_FSM(*this),
        m_helloInterval(std::chrono::milliseconds(150)),
        m_helloDeadInterval(std::chrono::milliseconds(500)),
        m_configSend_timer(m_io_context,
                           std::chrono::milliseconds(500),
                           3,
                           1,
                           boost::function<bool (bool)>(
                             boost::bind(&IpccImpl::evtConfRet,
                                         this,
                                         _1))),
        m_hello_timer(m_io_context,
                      m_helloInterval,
                      boost::function<bool (void)>(
                        boost::bind(&IpccImpl::evtHelloRet,
                                    this))),
        m_helloDead_timer(m_io_context,
                          m_helloDeadInterval,
                          boost::function<bool (void)>(
                            boost::bind(&IpccImpl::evtHoldTimer,
                                        this))),
        m_goingDown_timer(m_io_context,
                          m_helloDeadInterval,
                          boost::function<bool (void)>(
                            boost::bind(&IpccImpl::evtDownTimer,
                                        this))),
        m_TxSeqNum(0),
        m_RcvSeqNum(0),
        m_Observers(),
        m_neighborAdjacencyObservers(),
        m_fsm_mutex(),
        m_messageId(0),
        m_configMsg()
    {
      std::cout << "Node(" << m_node.getNodeId() << ").IPCC(localCCId = " << getLocalCCId()
                << ", remoteAddress = " << m_remote_endpoint.address().to_v4().to_ulong()
                << ", remotePortNumber = " << m_remote_endpoint.port() << ") ctor" << std::endl;
      {
        boost::unique_lock<boost::shared_mutex> guard(m_fsm_mutex);
        m_FSM.start();
      }
      registerObserver(m_node);
    }
    IpccImpl::~IpccImpl()
    {
      std::cout << "Node(" << m_node.getNodeId() << ").IPCC(localCCId = " << getLocalCCId()
                << ", remoteAddress = " << m_remote_endpoint.address().to_v4().to_ulong()
                << ", remotePortNumber = " << m_remote_endpoint.port() << ") dtor" << std::endl;
      boost::unique_lock<boost::shared_mutex> guard(m_fsm_mutex);
      m_FSM.stop();
    }
    void IpccImpl::do_enable()
    {
//      std::cout << "Node(" << m_node.getNodeId() << ").IPCC(localCCId = " << m_networkIFSocket.getLocalCCId()
//                << ", remoteAddress = " << m_remote_endpoint.address().to_v4().to_ulong()
//                << ", remotePortNumber = " << m_remote_endpoint.port() << ") enable" << std::endl;
      {
        boost::unique_lock<boost::shared_mutex> guard(m_fsm_mutex);
        m_FSM.start();
        m_FSM.process_event(EvBringUp());
      }
      static const lmp::cc::appl::ConfSnd stateConfSnd;
      const boost::optional<const lmp::cc::appl::State&>& activeState = getState();
      if (activeState &&
          *activeState == stateConfSnd )
      {
        std::cout << "Node(" << m_node.getNodeId() << ").IPCC(localCCId = " << getLocalCCId()
                  << ", remoteAddress = " << m_remote_endpoint.address().to_v4().to_ulong()
                  << ", remotePortNumber = " << m_remote_endpoint.port() << ") enable changed to ConfSnd state" << std::endl;
      }
    }
    void IpccImpl::do_disable()
    {
      {
        boost::unique_lock<boost::shared_mutex> guard(m_fsm_mutex);
        m_FSM.process_event(EvAdminDown());
      }
    }
    lmp::DWORD  IpccImpl::do_getLocalNodeId() const
    {
      return m_node.getNodeId();
    }
    lmp::DWORD  IpccImpl::do_getRemoteNodeId() const
    {
      return m_remoteNodeId;
    }
    lmp::DWORD  IpccImpl::do_getLocalCCId() const
    {
      return m_localCCId;
    }
    lmp::DWORD  IpccImpl::do_getRemoteCCId() const
    {
      return m_remoteCCId;
    }
    const boost::asio::ip::udp::endpoint& IpccImpl::do_getRemoteEndpoint() const
    {
      return m_remote_endpoint;
    }
    void IpccImpl::reconfigure(
      const obj::config::ast::HelloConfig&  helloConfig)
    {
      {
        boost::unique_lock<boost::shared_mutex> guard(m_fsm_mutex);
        m_FSM.process_event(EvReconfig());
      }
    }
    void IpccImpl::evtCCDown()
    {
      {
        boost::unique_lock<boost::shared_mutex> guard(m_fsm_mutex);
        m_FSM.process_event(EvCCDn());
        m_FSM.stop();
      }
    }
    bool IpccImpl::evtConfRet(
      bool  retryLimitReached)
    {
      {
        boost::unique_lock<boost::shared_mutex> guard(m_fsm_mutex);
        m_FSM.process_event(EvConfRet());
      }
      return !retryLimitReached;
    }
    bool IpccImpl::evtHelloRet()
    {
      {
        boost::unique_lock<boost::shared_mutex> guard(m_fsm_mutex);
        m_FSM.process_event(EvHelloRet());
      }
      return false;
    }
    bool IpccImpl::evtHoldTimer()
    {
      {
        boost::unique_lock<boost::shared_mutex> guard(m_fsm_mutex);
        m_FSM.process_event(EvHoldTimer());
      }
      return false;
    }
    bool IpccImpl::evtDownTimer()
    {
      {
        boost::unique_lock<boost::shared_mutex> guard(m_fsm_mutex);
        m_FSM.process_event(EvDownTimer());
      }
      return false;
    }
    boost::optional<const lmp::cc::appl::State&> IpccImpl::do_getState() const
    {
      boost::shared_lock<boost::shared_mutex> guard(m_fsm_mutex);
      return m_FSM.getActiveState();
    }
    void IpccImpl::do_registerObserver(
      appl::IpccObserverIF&  observer)
    {
      m_Observers.insert(&observer);
    }
    void IpccImpl::do_deregisterObserver(
  	appl::IpccObserverIF&  observer)
    {
      m_Observers.erase(&observer);
    }
    void IpccImpl::do_registerObserver(
      neighbor::NeighborAdjacencyObserverIF&  observer)
    {
      m_neighborAdjacencyObservers.insert(&observer);
    }
    void IpccImpl::do_deregisterObserver(
      neighbor::NeighborAdjacencyObserverIF&  observer)
    {
      m_neighborAdjacencyObservers.erase(&observer);
    }
    bool IpccImpl::do_hasActiveSetupRole() const
    {
      // std::cout << "activeSetupRole = " << (m_isActiveSetup ? "true" : "false") << std::endl;
      return m_isActiveSetup;
    }
    bool IpccImpl::do_isConntentionWinning(
      lmp::DWORD  remoteNodeId) const
    {
      return (getLocalNodeId() > remoteNodeId);
    }
    bool IpccImpl::do_isConfigAcceptable(
      const msg::ast::Config&  configMsg) const
    {
      // remoteNodeId, remoeCCId valid; HelloConfig in acceptable range
      bool isAcceptable = true;
      const lmp::obj::config::ast::ConfigObjectSequence&  configObjectSequence = configMsg.m_configObjects;
      for (std::vector<lmp::obj::config::ast::ConfigCTypes>::const_iterator iter = configObjectSequence.begin();
           iter != configObjectSequence.end() && isAcceptable;
           ++iter)
      {
        isAcceptable = boost::apply_visitor(ConfigCTypes_IsAcceptableVisitor(), *iter);
      }
      return isAcceptable;
    }

    void IpccImpl::do_sendConfig()
    {
      std::cout << "IPCC[" << getLocalCCId() << "].sendConfig()" << std::endl;
      // create and send Config
      if (m_configMsg)
      {
        m_configMsg.release();
      }
      {
        lmp::obj::config::ast::ConfigObjectSequence  configObjectSequence;
        {
          lmp::obj::config::ast::HelloConfig  helloConfig = { { true }, 0x009A, 0x01CF };
          configObjectSequence.push_back(lmp::obj::config::ast::ConfigCTypes(helloConfig));
        }
        lmp::msg::ast::Config  configMsg =
          { { isGoingDown(),
              isLMPRestart() },
            { { false }, getLocalCCId() },      // localCCId
            { { false }, ++m_messageId },      // messageId
            { { false }, getLocalNodeId() },      // localNodeId
            configObjectSequence  // configObjectss
          };
        m_configMsg = std::make_unique<lmp::msg::ast::Config>(configMsg);
        lmp::msg::ast::Message sendMessage = configMsg;
        lmp::cc::UDPMsgHandler::sendMessage(m_networkIFSocket,
                                            m_remote_endpoint,
                                            sendMessage);
      }
      m_configSend_timer.start();
    }

    void IpccImpl::do_sendConfig(
      const msg::ast::ConfigNack&  configNackMsg)
    {
      std::cout << "IPCC[" << getLocalCCId() << "].sendConfig()" << std::endl;
      // create and send Config
      if (m_configMsg)
      {
        m_configMsg.release();
      }
      {
        lmp::obj::config::ast::ConfigObjectSequence  configObjectSequence;
        {
          lmp::obj::config::ast::HelloConfig  helloConfig = { { true }, 0x009A, 0x01CF };
          configObjectSequence.push_back(lmp::obj::config::ast::ConfigCTypes(helloConfig));
        }
        lmp::msg::ast::Config  configMsg =
          { { isGoingDown(),
              isLMPRestart() },
            { { false }, getLocalCCId() },      // localCCId
            { { false }, ++m_messageId },      // messageId
            { { false }, getLocalNodeId() },      // localNodeId
            configObjectSequence  // configObjectss
          };
        m_configMsg = std::make_unique<lmp::msg::ast::Config>(configMsg);
        lmp::msg::ast::Message sendMessage = configMsg;
        lmp::cc::UDPMsgHandler::sendMessage(m_networkIFSocket,
                                            m_remote_endpoint,
                                            sendMessage);
      }
      m_configSend_timer.start();
    }

    void IpccImpl::do_resendConfig()
    {
      std::cout << "IPCC[" << getLocalCCId() << "].resendConfig()" << std::endl;
    }
    void IpccImpl::do_stopSendConfig()
    {
      std::cout << "IPCC[" << getLocalCCId() << "].stopSendConfig()" << std::endl;
      m_configSend_timer.stop();
      if (m_configMsg)
      {
        m_configMsg.release();
      }
    }
    void IpccImpl::do_sendConfigAck(
      const msg::ast::Config&  configMsg)
    {
      std::cout << "IPCC[" << getLocalCCId() << "].sendConfigAck()" << std::endl;
      updateConfig(configMsg);
      // create and send ConfigAck
      {
        lmp::msg::ast::ConfigAck configAckMsg =
          { { isGoingDown(),
              isLMPRestart() },
            { { false }, getLocalCCId() },      // localCCId
            { { false }, getLocalNodeId() },    // localNodeId
            { { false }, configMsg.m_localCCId.m_ccId },      // remoteCCId
            { { false }, configMsg.m_messageId.m_msgId },     // messageId
            { { false }, configMsg.m_localNodeId.m_nodeId }   // remoteNodeId
          };
        lmp::msg::ast::Message sendMessage = configAckMsg;
        lmp::cc::UDPMsgHandler::sendMessage(m_networkIFSocket,
                                            m_remote_endpoint,
                                            sendMessage);
      }
    }
    void IpccImpl::do_sendConfigNack(
      const msg::ast::Config&  configMsg)
    {
    }
    void IpccImpl::updateConfig(
      const msg::ast::Config&  configMsg)
    {
      std::cout << "IPCC[" << getLocalCCId() << "].updateConfig(" << configMsg << ")" << std::endl;
      if (m_remoteNodeId != configMsg.m_localNodeId.m_nodeId)
      {
        if (m_remoteNodeId)
        {
          for (NeighborAdjacencyObservers::iterator iter = m_neighborAdjacencyObservers.begin(),
                                                    end_iter = m_neighborAdjacencyObservers.end();
               iter != end_iter;
               ++iter)
          {
            if (*iter)
            {
              (*iter)->neighborAdjacencyRemoved(m_remoteNodeId, *this);
            }
          }
        }
        m_remoteNodeId = configMsg.m_localNodeId.m_nodeId;
        m_remoteCCId = configMsg.m_localCCId.m_ccId;
        for (IPCCObservers::iterator iter = m_Observers.begin(),
                                     end_iter = m_Observers.end();
             iter != end_iter;
             ++iter)
        {
          if (*iter)
          {
            (*iter)->notifyPeerIpccDiscovered(*this, m_remoteNodeId, m_remoteCCId);
          }
        }
        if (m_remoteNodeId)
        {
          for (NeighborAdjacencyObservers::iterator iter = m_neighborAdjacencyObservers.begin(),
                                                    end_iter = m_neighborAdjacencyObservers.end();
               iter != end_iter;
               ++iter)
          {
            if (*iter)
            {
              (*iter)->neighborAdjacencyAdded(m_remoteNodeId, *this);
            }
          }
        }
      }
      else if (m_remoteCCId != configMsg.m_localCCId.m_ccId)
      {
        m_remoteCCId = configMsg.m_localCCId.m_ccId;
      }
      std::cout << "IPCC[" << getLocalCCId() << "].updateConfig(): remoteNodeId = " << m_remoteNodeId
                << ", remoteCCId = " << m_remoteCCId << std::endl;
    }
    void IpccImpl::do_reportTransition(
      const appl::State&   sourceState,
      const appl::Event&   event,
      const appl::State&   targetState,
      const appl::Action&  action)
    {
      for (IPCCObservers::iterator iter = m_Observers.begin(),
    		                   end_iter = m_Observers.end();
           iter != end_iter;
           ++iter)
      {
        if (*iter)
        {
    	  (*iter)->notifyTransition(*this, sourceState, event, targetState, action);
        }
      }
//      fsm is still in sourceState
//      const boost::optional<const lmp::cc::appl::State&>& activeState = m_FSM.getActiveState();
//      if (activeState)
//      {
//        std::cout << "IPCC[" << getLocalCCId() << "].reportTransition(): fsm state = " << *activeState << std::endl;
//      }
    }
    void IpccImpl::do_sendHello()
    {
      std::cout << "IPCC[" << getLocalCCId() << "].sendHello()" << std::endl;
      if (m_TxSeqNum == std::numeric_limits<lmp::DWORD>::max())
      {
    	m_TxSeqNum = 2;
      }
      else
      {
    	++m_TxSeqNum;
      }
      // create and send Hello message and schedule Hello interval timer
      lmp::msg::ast::Hello  helloMsg =
        { { isGoingDown(),
            isLMPRestart() },
          { { false }, m_TxSeqNum, m_RcvSeqNum }     // hello
        };
      lmp::msg::ast::Message sendMessage = helloMsg;
      lmp::cc::UDPMsgHandler::sendMessage(m_networkIFSocket,
                                          m_remote_endpoint,
                                          sendMessage);
      m_hello_timer.start();
    }
    void IpccImpl::do_stopSendHello()
    {
      std::cout << "IPCC[" << getLocalCCId() << "].stopSendHello()" << std::endl;
      m_hello_timer.stop();
      m_helloDead_timer.stop();
    }
    void IpccImpl::do_processReceivedMessage(
      const msg::ast::Config&                  configMsg)
    {
      if (canAcceptNewConfig())
      {
      	if (isConfigAcceptable(configMsg))
      	{
          {
            boost::unique_lock<boost::shared_mutex> guard(m_fsm_mutex);
            m_FSM.process_event(EvNewConfOK(configMsg));
          }
      	}
      	else
      	{
          {
            boost::unique_lock<boost::shared_mutex> guard(m_fsm_mutex);
            m_FSM.process_event(EvNewConfErr(configMsg));
          }
      	}
      }
      else
      {
        if (isConntentionWinning(configMsg))
        {
          {
            boost::unique_lock<boost::shared_mutex> guard(m_fsm_mutex);
            m_FSM.process_event(EvContenWin(configMsg));
          }
        }
        else
        {
          {
            boost::unique_lock<boost::shared_mutex> guard(m_fsm_mutex);
            m_FSM.process_event(EvContenLost(configMsg));
          }
        }
      }
    }
    void IpccImpl::do_processReceivedMessage(
      const msg::ast::ConfigAck&               configAckMsg)
    {
      {
        boost::unique_lock<boost::shared_mutex> guard(m_fsm_mutex);
        m_FSM.process_event(EvConfDone(configAckMsg));
      }
    }
    void IpccImpl::do_processReceivedMessage(
      const msg::ast::ConfigNack&              configNackMsg)
    {
      {
        boost::unique_lock<boost::shared_mutex> guard(m_fsm_mutex);
        m_FSM.process_event(EvConfErr(configNackMsg));
      }
    }
    void IpccImpl::do_processReceivedMessage(
      const msg::ast::Hello&                   helloMsg)
    {
      std::cout << "Node(" << m_node.getNodeId() << ").IPCC["
                << getLocalCCId() << "].processReceivedMessage("
                << helloMsg << "): m_TxSeqNum = "
                << m_TxSeqNum << ", m_RcvSeqNum = " << m_RcvSeqNum << std::endl;
//      std::cout << "processReceivedMessage helloMsg.m_RcvSeqNum = " << helloMsg.m_RcvSeqNum
//    	        << ", m_TxSeqNum = " << m_TxSeqNum << std::endl;
//      If ((int) old_id - (int) new_id > 0) {
//            New value is less than old value;
//         }
      if (!( (boost::int32_t) m_RcvSeqNum -
             (boost::int32_t) helloMsg.m_hello.m_txSeqNum > 0))
      {
        m_RcvSeqNum = helloMsg.m_hello.m_txSeqNum;
      }
      if (helloMsg.m_hello.m_rcvSeqNum == m_TxSeqNum)
      {
        {
          boost::unique_lock<boost::shared_mutex> guard(m_fsm_mutex);
          m_FSM.process_event(EvHelloRcvd(helloMsg));
        }
      }
      else
      {
        {
          boost::unique_lock<boost::shared_mutex> guard(m_fsm_mutex);
          m_FSM.process_event(EvSeqNumErr(helloMsg));
        }
      }
    }
    void IpccImpl::do_processReceivedMessage(
      const msg::ast::UnknownMessage&             unknownMessage)
    {
      // report
    }
    bool IpccImpl::canAcceptNewConfig() const
    {
      static const lmp::cc::appl::ConfRcv stateConfRcv;
      static const lmp::cc::appl::Active stateActive;
      static const lmp::cc::appl::Up stateUp;
      const boost::optional<const lmp::cc::appl::State&>& activeState = getState();
      return
    	( activeState &&
    	  ( *activeState == stateConfRcv ||
    	    *activeState == stateActive ||
    	    *activeState == stateUp ) );
    }
    bool IpccImpl::isConntentionWinning(
      const msg::ast::Config&  configMsg) const
    {
      return do_isConntentionWinning(configMsg.m_localNodeId.m_nodeId);
    }
    bool IpccImpl::isGoingDown() const
    {
      return false;
    }
    bool IpccImpl::isLMPRestart() const
    {
      return false;
    }
  } // namespace cc
} // namespace lmp
