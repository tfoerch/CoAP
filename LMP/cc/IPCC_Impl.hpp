#ifndef LIBS_IPCC_IMPL_HPP_
#define LIBS_IPCC_IMPL_HPP_
/*
 * IPCC_Impl.hpp
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include "cc/IPCCApplicationIF.hpp"
#include "cc/IPCC_FSM.hpp"
#include "cc/IPCC_FSM_InvokeIF.hpp"
#include "cc/IPCC_Msg_ReceiveIF.hpp"
#include "base/ProtocolTypes.hpp"             // for DWORD
#include "base/RetransmitTimer.hpp"
#include "base/IntervalTimer.hpp"

#include <boost/asio/ip/udp.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/ptr_container/ptr_deque.hpp>  // for ptr_deque
#include <boost/thread.hpp>

#include <memory>
#include <chrono>

namespace boost { namespace asio { class io_context; } }

namespace lmp
{
  namespace node
  {
    class NodeApplicationIF;
  }
  namespace obj
  {
    namespace config
    {
      namespace ast
      {
        struct HelloConfig;
      }
    }
  }
  namespace cc
  {
    class NetworkIFSocketIF;
    namespace appl
    {
      class Action;
      class Event;
      class IpccObserverIF;
      class State;
    }
    class IpccImpl : public IpccApplicationIF,
                     public IpccFsmInvokeIF,
                     public IpccMsgReceiveIF
    {
    public:
      IpccImpl(
        lmp::DWORD                             localCCId,
        node::NodeApplicationIF&               node,
        NetworkIFSocketIF&                     networkIFSocket,
        boost::asio::io_context&               io_context,
        const boost::asio::ip::udp::endpoint&  remote_endpoint,
        bool                                   isActiveSetup);
      virtual ~IpccImpl();
      void reconfigure(
        const obj::config::ast::HelloConfig&  helloConfig);
      void evtCCDown();
      bool evtConfRet(
        bool  retryLimitReached);
      bool evtHelloRet();
      bool evtHoldTimer();
      bool evtDownTimer();
    private:
      typedef std::set<appl::IpccObserverIF*>                IPCCObservers;
      typedef std::set<neighbor::NeighborAdjacencyObserverIF*>  NeighborAdjacencyObservers;
      // implement IpccApplicationIF
      virtual void do_enable();
      virtual void do_disable();
      virtual lmp::DWORD do_getLocalNodeId() const;
      virtual boost::optional<const appl::State&> do_getState() const;
      virtual lmp::DWORD do_getRemoteNodeId() const;
      virtual lmp::DWORD do_getLocalCCId() const;
      virtual lmp::DWORD do_getRemoteCCId() const;
      virtual const boost::asio::ip::udp::endpoint& do_getRemoteEndpoint() const;
      virtual void do_registerObserver(
        appl::IpccObserverIF&  observer);
      virtual void do_deregisterObserver(
        appl::IpccObserverIF&  observer);
      virtual void do_registerObserver(
        neighbor::NeighborAdjacencyObserverIF&  observer);
      virtual void do_deregisterObserver(
        neighbor::NeighborAdjacencyObserverIF&  observer);
      // implement IpccFsmConnectIF
      virtual bool do_hasActiveSetupRole() const;
      virtual bool do_isConntentionWinning(
        lmp::DWORD  remoteNodeId) const;
      virtual bool do_isConfigAcceptable(
        const msg::ast::Config&  configMsg) const;
      virtual void do_sendConfig();
      virtual void do_sendConfig(
        const msg::ast::ConfigNack&  configNackMsg);
      virtual void do_resendConfig();
      virtual void do_stopSendConfig();
      virtual void do_sendConfigAck(
        const msg::ast::Config&  configMsg);
      virtual void do_sendConfigNack(
        const msg::ast::Config&  configMsg);
      virtual void do_reportTransition(
    	const appl::State&   sourceState,
    	const appl::Event&   event,
    	const appl::State&   targetState,
    	const appl::Action&  action);
      virtual void do_sendHello();
      virtual void do_stopSendHello();
      // implement IpccMsgReceiveIF
      virtual void do_processReceivedMessage(
    	const msg::ast::Config&                  configMsg);
      virtual void do_processReceivedMessage(
    	const msg::ast::ConfigAck&               configAckMsg);
      virtual void do_processReceivedMessage(
    	const msg::ast::ConfigNack&              configNackMsg);
      virtual void do_processReceivedMessage(
    	const msg::ast::Hello&                   helloMsg);
      virtual void do_processReceivedMessage(
        const msg::ast::UnknownMessage&             unknownMessage);
      // internal
      bool canAcceptNewConfig() const;
      bool isConntentionWinning(
    	const msg::ast::Config&  configMsg) const;
      void updateConfig(
        const msg::ast::Config&  configMsg);
      bool isGoingDown() const;
      bool isLMPRestart() const;
      IpccImpl(const IpccImpl&) = delete;
      void operator=(const IpccImpl&) = delete;

      lmp::DWORD                                        m_localCCId;
      node::NodeApplicationIF&                          m_node;
      NetworkIFSocketIF&                                m_networkIFSocket;
      boost::asio::io_context&                          m_io_context;
      boost::asio::ip::udp::endpoint                    m_remote_endpoint;
      lmp::DWORD                                        m_remoteNodeId;
      lmp::DWORD                                        m_remoteCCId;
      bool                                              m_isActiveSetup;
      FSM_IPCC                                          m_FSM;
      std::chrono::milliseconds                         m_helloInterval;
      std::chrono::milliseconds                         m_helloDeadInterval;
      base::RetransmitTimer                             m_configSend_timer;
      base::IntervalTimer                               m_hello_timer;
      base::IntervalTimer                               m_helloDead_timer;
      base::IntervalTimer                               m_goingDown_timer;
      lmp::DWORD                                        m_TxSeqNum;
      lmp::DWORD                                        m_RcvSeqNum;
      IPCCObservers                                     m_Observers;
      NeighborAdjacencyObservers                        m_neighborAdjacencyObservers;
      mutable boost::shared_mutex                       m_fsm_mutex;
      lmp::DWORD                                        m_messageId;
      std::unique_ptr<lmp::msg::ast::Config>            m_configMsg;
    };
  } // namespace cc
} // namespace lmp

#endif /* LIBS_IPCC_IMPL_HPP_ */
