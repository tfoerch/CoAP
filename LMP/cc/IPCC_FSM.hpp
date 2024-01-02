#ifndef LIBS_IPCC_FSM_HPP_
#define LIBS_IPCC_FSM_HPP_
/*
 * IPCC_FSM.hpp
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include "cc/IPCC_Event.hpp"
//#include "msg/ConfigAst.hpp"
//#include "msg/ConfigAckAst.hpp"

#include <boost/optional/optional.hpp>     // for optional
//#include <boost/smart_ptr/shared_ptr.hpp>  // for shared_ptr

#include <memory>

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
    }
  }
  namespace cc
  {
    namespace appl
    {
      class State;
    }
    class IpccFsmInvokeIF;
    struct SomeVisitor
    {
      template <class T>
      void visit_state(const T& astate)
      {
        // std::cout << "visiting state:" << astate.getApplState() << std::endl;
        theActiveState = boost::optional<const lmp::cc::appl::State&>(astate.getApplState());
      }
      boost::optional<const lmp::cc::appl::State&>  theActiveState;
    };
    class EvBringUp
    {
    public:
      static lmp::cc::appl::EvBringUp  theApplEvent;
    };
    class EvCCDn
    {
    public:
      static lmp::cc::appl::EvCCDn  theApplEvent;
    };
    class EvConfDone
    {
    public:
      explicit EvConfDone(
        const msg::ast::ConfigAck&  configAckMsg)
      : m_ConfigAckMsg(configAckMsg)
      {}
      const msg::ast::ConfigAck&  m_ConfigAckMsg;
      static lmp::cc::appl::EvConfDone  theApplEvent;
    };
    class EvConfErr
    {
    public:
      explicit EvConfErr(
        const msg::ast::ConfigNack&  configNackMsg)
      : m_ConfigNackMsg(configNackMsg)
      {}
      const msg::ast::ConfigNack&  m_ConfigNackMsg;
      static lmp::cc::appl::EvConfErr  theApplEvent;
    };
    class EvNewConfOK
    {
    public:
      explicit EvNewConfOK(
        const msg::ast::Config&  configMsg)
      : m_ConfigMsg(configMsg)
      {}
      const msg::ast::Config&  m_ConfigMsg;
      static lmp::cc::appl::EvNewConfOK  theApplEvent;
    };
    class EvNewConfErr
    {
    public:
      explicit EvNewConfErr(
        const msg::ast::Config&  configMsg)
      : m_ConfigMsg(configMsg)
      {}
      const msg::ast::Config&  m_ConfigMsg;
      static lmp::cc::appl::EvNewConfErr  theApplEvent;
    };
    class EvContenWin
    {
    public:
      explicit EvContenWin(
        const msg::ast::Config&  configMsg)
      : m_ConfigMsg(configMsg)
      {}
      const msg::ast::Config&  m_ConfigMsg;
      static lmp::cc::appl::EvContenWin  theApplEvent;
    };
    class EvContenLost
    {
    public:
      explicit EvContenLost(
        const msg::ast::Config&  configMsg)
      : m_ConfigMsg(configMsg)
      {}
      const msg::ast::Config&  m_ConfigMsg;
      static lmp::cc::appl::EvContenLost  theApplEvent;
    };
    class EvAdminDown
    {
    public:
      static lmp::cc::appl::EvAdminDown  theApplEvent;
    };
    class EvNbrGoesDn
    {
    public:
      static lmp::cc::appl::EvNbrGoesDn  theApplEvent;
    };
    class EvHelloRcvd
    {
    public:
      explicit EvHelloRcvd(
        const msg::ast::Hello&  helloMsg)
      : m_helloMsg(helloMsg)
      {}
      const msg::ast::Hello&  m_helloMsg;
      static lmp::cc::appl::EvHelloRcvd  theApplEvent;
    };
    class EvHoldTimer
    {
    public:
      static lmp::cc::appl::EvHoldTimer  theApplEvent;
    };
    class EvSeqNumErr
    {
    public:
      explicit EvSeqNumErr(
        const msg::ast::Hello&  helloMsg)
      : m_helloMsg(helloMsg)
      {}
      const msg::ast::Hello&  m_helloMsg;
      static lmp::cc::appl::EvSeqNumErr  theApplEvent;
    };
    class EvReconfig
    {
    public:
      static lmp::cc::appl::EvReconfig  theApplEvent;
    };
    class EvConfRet
    {
    public:
      static lmp::cc::appl::EvConfRet  theApplEvent;
    };
    class EvHelloRet
    {
    public:
      static lmp::cc::appl::EvHelloRet  theApplEvent;
    };
    class EvDownTimer
    {
    public:
      static lmp::cc::appl::EvDownTimer  theApplEvent;
    };
    class FSM_IPCC
    {
    public:
      explicit FSM_IPCC(
        IpccFsmInvokeIF&  ipcc);
      ~FSM_IPCC();
      // forward-declare nested type. This will inherit msm::back::state_machine<...>
      bool start();
      bool stop();
      boost::optional<const lmp::cc::appl::State&> getActiveState() const;
      template <class Event>
      bool process_event(const Event& e);
      struct FsmIpccImpl;
      // with shared_ptr, you don't need the complete type yet.
      std::unique_ptr<FsmIpccImpl> theFSMImpl;
      FSM_IPCC(const FSM_IPCC&) = delete;
      void operator=(const FSM_IPCC&) = delete;
    };
  } // namespace cc
} // namespace lmp

#endif /* LIBS_IPCC_FSM_HPP_ */
