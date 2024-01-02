/*
 * IPCC_FSM.cpp
 *
 *  Created on: 21.02.2015
 *      Author: tom
 */


#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_VECTOR_SIZE 40
#define BOOST_MPL_LIMIT_MAP_SIZE 40

#include "IPCC_FSM.hpp"
#include "IPCC_ObserverIF.hpp"                            // for Action, etc
#include "IPCC_FSM_InvokeIF.hpp"
#include "cc/IPCC_State.hpp"
#include "cc/IPCC_Action.hpp"

#include <boost/core/ref.hpp>
#include <boost/mpl/aux_/adl_barrier.hpp>                 // for mpl
#include <boost/mpl/vector.hpp>                           // for vector
#include <boost/msm/active_state_switching_policies.hpp>  // for msm
#include <boost/msm/back/args.hpp>                        // for args
#include <boost/msm/back/state_machine.hpp>
//front-end
#include <boost/msm/front/functor_row.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/states.hpp>                     // for state
//#include <boost/smart_ptr/detail/operator_bool.hpp>
#include <iostream>                                       // for operator<<, etc
#include <typeinfo>                                       // for type_info

namespace boost
{
  namespace msm
  {
    namespace front
    {
      struct none;
    }
  }
}

namespace msm = boost::msm;
namespace mpl = boost::mpl;
using namespace msm::front;
// for And_ operator
//using namespace msm::front::euml;

namespace lmp
{
  namespace cc
  {
    // overwrite of the base state (not default)
    struct my_visitable_state
    {
      // signature of the accept function
      typedef msm::back::args<void, SomeVisitor&> accept_sig;

      // we also want polymorphic states
      virtual ~my_visitable_state() {}
      virtual const lmp::cc::appl::State& getApplState() const
      {
        static lmp::cc::appl::Down dummy;
        return dummy;
      }
      void accept(SomeVisitor& visitor) const
      {
        visitor.visit_state(*this);
      }
    };
    // front-end: define the FSM structure
    struct cc_fsm_ : public msm::front::state_machine_def<cc_fsm_, my_visitable_state>
    {
      explicit cc_fsm_(IpccFsmInvokeIF&  ipcc);
      IpccFsmInvokeIF&  theIPCC;
      // states
      struct Down_tag {};
      // struct Down : public msm::front::euml::func_state<Down_tag>
      struct Down : public msm::front::state<my_visitable_state>
//      struct Down : public msm::front::euml::func_state<Down_tag,
//	                                                    NoAction,
//														NoAction,
//														::boost::fusion::vector<>,
//														::boost::mpl::vector0<>,
//														::boost::mpl::vector0<>,
//														my_visitable_state>
      {
    	virtual const lmp::cc::appl::State& getApplState() const
    	{
    	  return theApplState;
    	}
//     	void accept(SomeVisitor& visitor) const
//      	{
//      	  std::cout << "accept visitor" << std::endl;
//      	  visitor.visit_state(*this);
//      	}
    	static lmp::cc::appl::Down  theApplState;
      };
      struct ConfSnd_Entry
      {
        template <class Event,class FSM,class STATE>
        void operator()(Event const&,FSM&,STATE& );
      };
      struct ConfSnd_Exit
      {
        template <class Event,class FSM,class STATE>
        void operator()(Event const&,FSM&,STATE& );
      };
      struct ConfSnd_tag {};
      //struct ConfSnd: public msm::front::euml::func_state<ConfSnd_tag, ConfSnd_Entry, ConfSnd_Exit>
      struct ConfSnd : public msm::front::state<my_visitable_state>
//      struct ConfSnd : public msm::front::euml::func_state<ConfSnd_tag,
//	                                                       ConfSnd_Entry,
//														   ConfSnd_Exit,
//														   ::boost::fusion::vector<>,
//														   ::boost::mpl::vector0<>,
//														   ::boost::mpl::vector0<>,
//														   my_visitable_state>
      {
      	virtual const lmp::cc::appl::State& getApplState() const
      	{
      	  return theApplState;
      	}
//      	void accept(SomeVisitor& visitor) const
//      	{
//      	  std::cout << "accept visitor" << std::endl;
//      	  visitor.visit_state(*this);
//      	}
    	static lmp::cc::appl::ConfSnd  theApplState;
      };
      struct ConfRcv_tag {};
      //struct ConfRcv: public msm::front::euml::func_state<ConfRcv_tag>
      struct ConfRcv : public msm::front::state<my_visitable_state>
//      struct ConfRcv : public msm::front::euml::func_state<ConfRcv_tag,
//	                                                       NoAction,
//														   NoAction,
//														   ::boost::fusion::vector<>,
//														   ::boost::mpl::vector0<>,
//														   ::boost::mpl::vector0<>,
//														   my_visitable_state>
      {
      	virtual const lmp::cc::appl::State& getApplState() const
      	{
      	  return theApplState;
      	}
//      	void accept(SomeVisitor& visitor) const
//      	{
//      	  std::cout << "accept visitor" << std::endl;
//      	  visitor.visit_state(*this);
//      	}
    	static lmp::cc::appl::ConfRcv  theApplState;
      };
      struct Active_Entry
      {
        template <class Event,class FSM,class STATE>
        void operator()(Event const&,FSM&,STATE& );
      };
      struct Active_Exit
      {
        template <class Event,class FSM,class STATE>
        void operator()(Event const&,FSM&,STATE& );
      };
      struct Active_tag {};
      //struct Active : public msm::front::euml::func_state<Active_tag, Active_Entry, Active_Exit>
      struct Active : public msm::front::state<my_visitable_state>
//      struct Active : public msm::front::euml::func_state<Active_tag,
//	                                                      Active_Entry,
//	                                                      Active_Exit,
//														  ::boost::fusion::vector<>,
//														  ::boost::mpl::vector0<>,
//													      ::boost::mpl::vector0<>,
//													      my_visitable_state>
      {
      	virtual const lmp::cc::appl::State& getApplState() const
      	{
      	  return theApplState;
      	}
//    	void accept(SomeVisitor& visitor) const
//    	{
//    	  std::cout << "accept visitor" << std::endl;
//    	  visitor.visit_state(*this);
//    	}
    	static lmp::cc::appl::Active  theApplState;
      };
      struct Up_Entry
      {
        template <class Event,class FSM,class STATE>
        void operator()(Event const&,FSM&,STATE& );
      };
      struct Up_Exit
      {
        template <class Event,class FSM,class STATE>
        void operator()(Event const&,FSM&,STATE& );
      };
      struct Up_tag {};
      //struct Up : public msm::front::euml::func_state<Up_tag, Up_Entry, Up_Exit>
      struct Up : public msm::front::state<my_visitable_state>
//      struct Up : public msm::front::euml::func_state<Up_tag,
//	                                                  Up_Entry,
//	                                                  Up_Exit,
//													  ::boost::fusion::vector<>,
//													  ::boost::mpl::vector0<>,
//													  ::boost::mpl::vector0<>,
//													  my_visitable_state>
      {
      	virtual const lmp::cc::appl::State& getApplState() const
      	{
      	  return theApplState;
      	}
//      	void accept(SomeVisitor& visitor) const
//      	{
//      	  std::cout << "accept visitor" << std::endl;
//      	  visitor.visit_state(*this);
//      	}
    	static lmp::cc::appl::Up  theApplState;
      };
      struct GoingDown_Entry
      {
        template <class Event,class FSM,class STATE>
        void operator()(Event const&,FSM&,STATE& );
      };
      struct GoingDown_Exit
      {
        template <class Event,class FSM,class STATE>
        void operator()(Event const&,FSM&,STATE& );
      };
      struct GoingDown_tag {};
      //struct GoingDown : public msm::front::euml::func_state<GoingDown_tag, GoingDown_Entry, GoingDown_Exit>
      struct GoingDown : public msm::front::state<my_visitable_state>
//      struct GoingDown : public msm::front::euml::func_state<GoingDown_tag,
//	                                                         GoingDown_Entry,
//	                                                         GoingDown_Exit,
//													         ::boost::fusion::vector<>,
//													         ::boost::mpl::vector0<>,
//													         ::boost::mpl::vector0<>,
//													         my_visitable_state>
      {
      	virtual const lmp::cc::appl::State& getApplState() const
      	{
      	  return theApplState;
      	}
//      	void accept(SomeVisitor& visitor) const
//      	{
//      	  std::cout << "accept visitor" << std::endl;
//      	  visitor.visit_state(*this);
//      	}
    	static lmp::cc::appl::GoingDown  theApplState;
      };
      // the initial state of the control channel SM. Must be defined
      typedef Down initial_state;
      // transition actions
      struct SendConfig
      {
        template <class EVT,class FSM,class SourceState,class TargetState>
        void operator()(EVT const&, FSM&,SourceState& ,TargetState& );
        template <class FSM,class SourceState,class TargetState>
        void operator()(EvConfErr const& evt, FSM& fsm,SourceState& src,TargetState& tgt);
    	static lmp::cc::appl::ActionTag<lmp::cc::appl::Action::ActionSendConfig>  theActionTag;
      };
      struct StopSendConfig
      {
        template <class EVT,class FSM,class SourceState,class TargetState>
        void operator()(EVT const&, FSM&,SourceState& ,TargetState& );
    	static lmp::cc::appl::ActionTag<lmp::cc::appl::Action::ActionStopSendConfig>  theActionTag;
      };
      struct ResendConfig
      {
        template <class EVT,class FSM,class SourceState,class TargetState>
        void operator()(EVT const&, FSM&,SourceState& ,TargetState& );
    	static lmp::cc::appl::ActionTag<lmp::cc::appl::Action::ActionResendConfig>  theActionTag;
      };
      struct SendConfigAck
      {
        template <class EVT,class FSM,class SourceState,class TargetState>
        void operator()(EVT const&, FSM&,SourceState& ,TargetState& );
        template <class FSM,class SourceState,class TargetState>
        void operator()(EvContenLost const& evt, FSM& fsm,SourceState& src,TargetState& tgt);
        template <class FSM,class SourceState,class TargetState>
        void operator()(EvNewConfOK const& evt, FSM& fsm,SourceState& src,TargetState& tgt);
    	static lmp::cc::appl::ActionTag<lmp::cc::appl::Action::ActionSendConfigAck>  theActionTag;
      };
      struct SendConfigNack
      {
        template <class EVT,class FSM,class SourceState,class TargetState>
        void operator()(EVT const&, FSM&,SourceState& ,TargetState& );
        template <class FSM,class SourceState,class TargetState>
        void operator()(EvContenLost const& evt, FSM& fsm,SourceState& src, TargetState& tgt);
        template <class FSM,class SourceState,class TargetState>
        void operator()(EvNewConfErr const& evt, FSM& fsm,SourceState& src, TargetState& tgt);
    	static lmp::cc::appl::ActionTag<lmp::cc::appl::Action::ActionSendConfigNack>  theActionTag;
      };
      struct SendHello
      {
        template <class EVT,class FSM,class SourceState,class TargetState>
        void operator()(EVT const&, FSM&,SourceState& ,TargetState& );
    	static lmp::cc::appl::ActionTag<lmp::cc::appl::Action::ActionSendHello>  theActionTag;
      };
      struct StopSendHello
      {
        template <class EVT,class FSM,class SourceState,class TargetState>
        void operator()(EVT const&, FSM&,SourceState& ,TargetState& );
    	static lmp::cc::appl::ActionTag<lmp::cc::appl::Action::ActionStopSendHello>  theActionTag;
      };
      struct SetCCDownFlag
      {
        template <class EVT,class FSM,class SourceState,class TargetState>
        void operator()(EVT const&, FSM&,SourceState& ,TargetState& );
    	static lmp::cc::appl::ActionTag<lmp::cc::appl::Action::ActionSetCCDownFlag>  theActionTag;
      };
      struct ClearCCDownFlag
      {
        template <class EVT,class FSM,class SourceState,class TargetState>
        void operator()(EVT const&, FSM&,SourceState& ,TargetState& );
    	static lmp::cc::appl::ActionTag<lmp::cc::appl::Action::ActionClearCCDownFlag>  theActionTag;
      };
      struct NoAction
      {
        template <class EVT,class FSM,class SourceState,class TargetState>
        void operator()(EVT const&, FSM&,SourceState& ,TargetState& );
    	static lmp::cc::appl::ActionTag<lmp::cc::appl::Action::ActionNoAction>  theActionTag;
      };
      // guard conditions
      struct ActiveConfig
      {
        template <class EVT,class FSM,class SourceState,class TargetState>
        bool operator()(EVT const& evt,FSM& fsm,SourceState& src,TargetState& tgt);
      };
      struct PassiveConfig
      {
        template <class EVT,class FSM,class SourceState,class TargetState>
        bool operator()(EVT const& evt,FSM& fsm,SourceState& src,TargetState& tgt);
      };
      struct AcceptableConfig
      {
        template <class EVT,class FSM,class SourceState,class TargetState>
        bool operator()(EVT const& evt,FSM& fsm,SourceState& src,TargetState& tgt);
        template <class FSM,class SourceState,class TargetState>
        bool operator()(EvContenLost const& evt, FSM& fsm,SourceState& src,TargetState& tgt);
      };
      struct NotAcceptableConfig
      {
        template <class EVT,class FSM,class SourceState,class TargetState>
        bool operator()(EVT const& evt,FSM& fsm,SourceState& src,TargetState& tgt);
        template <class FSM,class SourceState,class TargetState>
        bool operator()(EvContenLost const& evt, FSM& fsm,SourceState& src,TargetState& tgt);
      };
      // Transition table for player
      struct transition_table : mpl::vector<
      //    Start       Event         Next        Action                           Guard
      //  +-----------+-------------+-----------+--------------------------------+----------------------+
      Row < Down      , EvBringUp   , ConfSnd   , SendConfig                     , ActiveConfig         >,
      Row < Down      , EvBringUp   , ConfRcv   , NoAction                       , PassiveConfig        >,
      //  +-----------+-------------+-----------+--------------------------------+----------------------+
      Row < ConfSnd   , EvCCDn      , Down      , StopSendConfig                 , none                 >,
      Row < ConfSnd   , EvAdminDown , Down      , StopSendConfig                 , none                 >,
      Row < ConfSnd   , EvConfErr   , ConfSnd   , SendConfig                     , none                 >,
      Row < ConfSnd   , EvContenWin , ConfSnd   , NoAction                       , none                 >,
      Row < ConfSnd   , EvReconfig  , ConfSnd   , SendConfig                     , none                 >,
      Row < ConfSnd   , EvConfRet   , ConfSnd   , ResendConfig                   , none                 >,
      Row < ConfSnd   , EvContenLost, ConfRcv   , ActionSequence_
                                                  <mpl::vector<SendConfigNack,
                                                               StopSendConfig> > , NotAcceptableConfig  >,
      Row < ConfSnd   , EvConfDone  , Active    , ActionSequence_
                                                  <mpl::vector<StopSendConfig,
                                                               SendHello> >      , none                 >,
      Row < ConfSnd   , EvContenLost, Active    , ActionSequence_
                                                  <mpl::vector<StopSendConfig,
                                                               SendConfigAck,
                                                               SendHello> >      , AcceptableConfig     >,
      //  +-----------+-------------+-----------+--------------------------------+----------------------+
      Row < ConfRcv   , EvCCDn      , Down      , NoAction                       , none                 >,
      Row < ConfRcv   , EvAdminDown , Down      , NoAction                       , none                 >,
      Row < ConfRcv   , EvNewConfErr, ConfRcv   , SendConfigNack                 , none                 >,
      Row < ConfRcv   , EvReconfig  , ConfRcv   , NoAction                       , none                 >,
      Row < ConfRcv   , EvNewConfOK , Active    , ActionSequence_
                                                  <mpl::vector<SendConfigAck,
                                                               SendHello> >      , none                 >,
      //  +-----------+-------------+-----------+--------------------------------+----------------------+
      Row < Active    , EvCCDn      , Down      , StopSendHello                  , none                 >,
      Row < Active    , EvAdminDown , GoingDown , SetCCDownFlag                  , none                 >,
      Row < Active    , EvNbrGoesDn , Down      , StopSendHello                  , none                 >,
      Row < Active    , EvReconfig  , ConfSnd   , ActionSequence_
                                                  <mpl::vector<SendConfig,
                                                               StopSendHello> >  , none                 >,
      Row < Active    , EvHoldTimer , ConfSnd   , ActionSequence_
                                                  <mpl::vector<SendConfig,
                                                               StopSendHello> >  , ActiveConfig         >,
      Row < Active    , EvHoldTimer , ConfRcv   , StopSendHello                  , PassiveConfig        >,
      Row < Active    , EvNewConfErr, ConfRcv   , ActionSequence_
                                                  <mpl::vector<SendConfigNack,
                                                               StopSendHello> >  , none                 >,
      Row < Active    , EvNewConfOK , Active    , NoAction                       , none                 >,
      Row < Active    , EvSeqNumErr , Active    , NoAction                       , none                 >,
      Row < Active    , EvHelloRet  , Active    , SendHello                      , none                 >,
      Row < Active    , EvHelloRcvd , Up        , NoAction                       , none                 >,
      //  +-----------+-------------+-----------+--------------------------------+----------------------+
      Row < Up        , EvCCDn      , Down      , StopSendHello                  , none                 >,
      Row < Up        , EvAdminDown , GoingDown , SetCCDownFlag                  , none                 >,
      Row < Up        , EvNbrGoesDn , Down      , StopSendHello                  , none                 >,
      Row < Up        , EvReconfig  , ConfSnd   , ActionSequence_
                                                  <mpl::vector<SendConfig,
                                                               StopSendHello> >  , none                 >,
      Row < Up        , EvHoldTimer , ConfSnd   , ActionSequence_
                                                  <mpl::vector<SendConfig,
                                                               StopSendHello> >  , ActiveConfig         >,
      Row < Up        , EvHoldTimer , ConfRcv   , StopSendHello                  , PassiveConfig        >,
      Row < Up        , EvNewConfErr, ConfRcv   , ActionSequence_
                                                  <mpl::vector<SendConfigNack,
                                                               StopSendHello> >  , none                 >,
      Row < Up        , EvNewConfOK , Active    , NoAction                       , none                 >,
      Row < Up        , EvSeqNumErr , Up        , NoAction                       , none                 >,
      Row < Up        , EvHelloRet  , Up        , SendHello                      , none                 >,
      Row < Up        , EvHelloRcvd , Up        , NoAction                       , none                 >,
      //  +-----------+-------------+-----------+--------------------------------+----------------------+
      Row < GoingDown , EvNbrGoesDn , Down      , StopSendHello                  , none                 >,
      Row < GoingDown , EvDownTimer , Down      , StopSendHello                  , none                 >
      //  +-----------+-------------+-----------+--------------------------------+----------------------+
      > {};
      // Replaces the default no-transition response.
      template <class FSM,class Event>
      void no_transition(Event const& e, FSM&, int state);
    };
    // static member initialization
    lmp::cc::appl::EvBringUp     EvBringUp::theApplEvent;
    lmp::cc::appl::EvCCDn        EvCCDn::theApplEvent;
    lmp::cc::appl::EvConfDone    EvConfDone::theApplEvent;
    lmp::cc::appl::EvConfErr     EvConfErr::theApplEvent;
    lmp::cc::appl::EvNewConfOK   EvNewConfOK::theApplEvent;
    lmp::cc::appl::EvNewConfErr  EvNewConfErr::theApplEvent;
    lmp::cc::appl::EvContenWin   EvContenWin::theApplEvent;
    lmp::cc::appl::EvContenLost  EvContenLost::theApplEvent;
    lmp::cc::appl::EvAdminDown   EvAdminDown::theApplEvent;
    lmp::cc::appl::EvNbrGoesDn   EvNbrGoesDn::theApplEvent;
    lmp::cc::appl::EvHelloRcvd   EvHelloRcvd::theApplEvent;
    lmp::cc::appl::EvHoldTimer   EvHoldTimer::theApplEvent;
    lmp::cc::appl::EvSeqNumErr   EvSeqNumErr::theApplEvent;
    lmp::cc::appl::EvReconfig    EvReconfig::theApplEvent;
    lmp::cc::appl::EvConfRet     EvConfRet::theApplEvent;
    lmp::cc::appl::EvHelloRet    EvHelloRet::theApplEvent;
    lmp::cc::appl::EvDownTimer   EvDownTimer::theApplEvent;

    lmp::cc::appl::Down       cc_fsm_::Down::theApplState;
    lmp::cc::appl::ConfSnd    cc_fsm_::ConfSnd::theApplState;
    lmp::cc::appl::ConfRcv    cc_fsm_::ConfRcv::theApplState;
    lmp::cc::appl::Active     cc_fsm_::Active::theApplState;
    lmp::cc::appl::Up         cc_fsm_::Up::theApplState;
    lmp::cc::appl::GoingDown  cc_fsm_::GoingDown::theApplState;

    lmp::cc::appl::ActionTag<lmp::cc::appl::Action::ActionSendConfig> cc_fsm_::SendConfig::theActionTag;
    lmp::cc::appl::ActionTag<lmp::cc::appl::Action::ActionStopSendConfig> cc_fsm_::StopSendConfig::theActionTag;
    lmp::cc::appl::ActionTag<lmp::cc::appl::Action::ActionResendConfig> cc_fsm_::ResendConfig::theActionTag;
    lmp::cc::appl::ActionTag<lmp::cc::appl::Action::ActionSendConfigAck> cc_fsm_::SendConfigAck::theActionTag;
    lmp::cc::appl::ActionTag<lmp::cc::appl::Action::ActionSendConfigNack> cc_fsm_::SendConfigNack::theActionTag;
    lmp::cc::appl::ActionTag<lmp::cc::appl::Action::ActionSendHello> cc_fsm_::SendHello::theActionTag;
    lmp::cc::appl::ActionTag<lmp::cc::appl::Action::ActionStopSendHello> cc_fsm_::StopSendHello::theActionTag;
    lmp::cc::appl::ActionTag<lmp::cc::appl::Action::ActionSetCCDownFlag> cc_fsm_::SetCCDownFlag::theActionTag;
    lmp::cc::appl::ActionTag<lmp::cc::appl::Action::ActionClearCCDownFlag> cc_fsm_::ClearCCDownFlag::theActionTag;
    lmp::cc::appl::ActionTag<lmp::cc::appl::Action::ActionNoAction> cc_fsm_::NoAction::theActionTag;

    cc_fsm_::cc_fsm_(IpccFsmInvokeIF&  ipcc) : theIPCC(ipcc)
    {}

    template <class Event,class FSM,class STATE>
    void cc_fsm_::ConfSnd_Entry::operator()(Event const& ,FSM& ,STATE& )
    {
      std::cout << "entering: ConfSnd" << std::endl;
    }
    template <class Event,class FSM,class STATE>
    void cc_fsm_::ConfSnd_Exit::operator()(Event const& ,FSM& ,STATE& )
    {
      std::cout << "leaving: ConfSnd" << std::endl;
    }

    template <class Event,class FSM,class STATE>
    void cc_fsm_::Active_Entry::operator()(Event const& ,FSM& ,STATE& )
    {
      std::cout << "entering: Active" << std::endl;
    }
    template <class Event,class FSM,class STATE>
    void cc_fsm_::Active_Exit::operator()(Event const& ,FSM& ,STATE& )
    {
      std::cout << "leaving: Active" << std::endl;
    }

    template <class Event,class FSM,class STATE>
    void cc_fsm_::Up_Entry::operator()(Event const& ,FSM& ,STATE& )
    {
      std::cout << "entering: Up" << std::endl;
    }
    template <class Event,class FSM,class STATE>
    void cc_fsm_::Up_Exit::operator()(Event const& ,FSM& ,STATE& )
    {
      std::cout << "leaving: Up" << std::endl;
    }

    template <class Event,class FSM,class STATE>
    void cc_fsm_::GoingDown_Entry::operator()(Event const& ,FSM& ,STATE& )
    {
      std::cout << "entering: GoingDown" << std::endl;
    }
    template <class Event,class FSM,class STATE>
    void cc_fsm_::GoingDown_Exit::operator()(Event const& ,FSM& ,STATE& )
    {
      std::cout << "leaving: GoingDown" << std::endl;
    }

    template <class EVT,class FSM,class SourceState,class TargetState>
    void cc_fsm_::SendConfig::operator()(EVT const&, FSM& fsm, SourceState&, TargetState&)
    {
      fsm.theIPCC.sendConfig();
      fsm.theIPCC.reportTransition(SourceState::theApplState, EVT::theApplEvent, TargetState::theApplState, theActionTag);
    }
    template <class FSM,class SourceState,class TargetState>
    void cc_fsm_::SendConfig::operator()(EvConfErr const& evt, FSM& fsm,SourceState& src,TargetState& tgt)
    {
      fsm.theIPCC.sendConfig(evt.m_ConfigNackMsg);
      fsm.theIPCC.reportTransition(SourceState::theApplState, EvConfErr::theApplEvent, TargetState::theApplState, theActionTag);
    }

    template <class EVT,class FSM,class SourceState,class TargetState>
    void cc_fsm_::StopSendConfig::operator()(EVT const&, FSM& fsm,SourceState& ,TargetState& )
    {
      fsm.theIPCC.reportTransition(SourceState::theApplState, EVT::theApplEvent, TargetState::theApplState, theActionTag);
      fsm.theIPCC.stopSendConfig();
    }

    template <class EVT,class FSM,class SourceState,class TargetState>
    void cc_fsm_::ResendConfig::operator()(EVT const&, FSM& fsm,SourceState& ,TargetState& )
    {
      fsm.theIPCC.resendConfig();
      fsm.theIPCC.reportTransition(SourceState::theApplState, EVT::theApplEvent, TargetState::theApplState, theActionTag);
    }

    template <class EVT,class FSM,class SourceState,class TargetState>
    void cc_fsm_::SendConfigAck::operator()(EVT const&, FSM& fsm,SourceState& ,TargetState& )
    {
      fsm.theIPCC.reportTransition(SourceState::theApplState, EVT::theApplEvent, TargetState::theApplState, theActionTag);
    }
    template <class FSM,class SourceState,class TargetState>
    void cc_fsm_::SendConfigAck::operator()(EvContenLost const& evt, FSM& fsm,SourceState& src,TargetState& tgt)
    {
      fsm.theIPCC.sendConfigAck(evt.m_ConfigMsg);
      fsm.theIPCC.reportTransition(SourceState::theApplState, EvContenLost::theApplEvent, TargetState::theApplState, theActionTag);
    }
    template <class FSM,class SourceState,class TargetState>
    void cc_fsm_::SendConfigAck::operator()(EvNewConfOK const& evt, FSM& fsm,SourceState& src,TargetState& tgt)
    {
      fsm.theIPCC.sendConfigAck(evt.m_ConfigMsg);
      fsm.theIPCC.reportTransition(SourceState::theApplState, EvNewConfOK::theApplEvent, TargetState::theApplState, theActionTag);
    }

    template <class EVT,class FSM,class SourceState,class TargetState>
    void cc_fsm_::SendConfigNack::operator()(EVT const&, FSM& fsm,SourceState& ,TargetState& )
    {
      fsm.theIPCC.reportTransition(SourceState::theApplState, EVT::theApplEvent, TargetState::theApplState, theActionTag);
    }
    template <class FSM,class SourceState,class TargetState>
    void cc_fsm_::SendConfigNack::operator()(EvContenLost const& evt, FSM& fsm,SourceState& ,TargetState& )
    {
      fsm.theIPCC.sendConfigNack(evt.m_ConfigMsg);
      fsm.theIPCC.reportTransition(SourceState::theApplState, EvContenLost::theApplEvent, TargetState::theApplState, theActionTag);
    }
    template <class FSM,class SourceState,class TargetState>
    void cc_fsm_::SendConfigNack::operator()(EvNewConfErr const& evt, FSM& fsm,SourceState& src, TargetState& tgt)
    {
      fsm.theIPCC.sendConfigNack(evt.m_ConfigMsg);
      fsm.theIPCC.reportTransition(SourceState::theApplState, EvContenLost::theApplEvent, TargetState::theApplState, theActionTag);
    }

    template <class EVT,class FSM,class SourceState,class TargetState>
    void cc_fsm_::SendHello::operator()(EVT const&, FSM& fsm,SourceState& ,TargetState& )
    {
      fsm.theIPCC.reportTransition(SourceState::theApplState, EVT::theApplEvent, TargetState::theApplState, theActionTag);
      fsm.theIPCC.sendHello();
    }
    template <class EVT,class FSM,class SourceState,class TargetState>
    void cc_fsm_::StopSendHello::operator()(EVT const&, FSM& fsm,SourceState& ,TargetState& )
    {
      fsm.theIPCC.reportTransition(SourceState::theApplState, EVT::theApplEvent, TargetState::theApplState, theActionTag);
      fsm.theIPCC.stopSendHello();
      }
    template <class EVT,class FSM,class SourceState,class TargetState>
    void cc_fsm_::SetCCDownFlag::operator()(EVT const&, FSM& fsm,SourceState& ,TargetState& )
    {
      fsm.theIPCC.reportTransition(SourceState::theApplState, EVT::theApplEvent, TargetState::theApplState, theActionTag);
    }
    template <class EVT,class FSM,class SourceState,class TargetState>
    void cc_fsm_::ClearCCDownFlag::operator()(EVT const&, FSM& fsm,SourceState& ,TargetState& )
    {
      fsm.theIPCC.reportTransition(SourceState::theApplState, EVT::theApplEvent, TargetState::theApplState, theActionTag);
    }
    template <class EVT,class FSM,class SourceState,class TargetState>
    void cc_fsm_::NoAction::operator()(EVT const&, FSM& fsm,SourceState& ,TargetState& )
    {
      fsm.theIPCC.reportTransition(SourceState::theApplState, EVT::theApplEvent, TargetState::theApplState, theActionTag);
    }

    // guard conditions
    template <class EVT,class FSM,class SourceState,class TargetState>
    bool cc_fsm_::ActiveConfig::operator()(EVT const& evt,FSM& fsm,SourceState& src,TargetState& tgt)
    {
      return fsm.theIPCC.hasActiveSetupRole();
    }
    template <class EVT,class FSM,class SourceState,class TargetState>
    bool cc_fsm_::PassiveConfig::operator()(EVT const& evt,FSM& fsm,SourceState& src,TargetState& tgt)
    {
      return !fsm.theIPCC.hasActiveSetupRole();
    }
    template <class EVT,class FSM,class SourceState,class TargetState>
    bool cc_fsm_::AcceptableConfig::operator()(EVT const& evt,FSM& fsm,SourceState& src,TargetState& tgt)
    {
      return false;
    }
    template <class FSM,class SourceState,class TargetState>
    bool cc_fsm_::AcceptableConfig::operator()(EvContenLost const& evt, FSM& fsm,SourceState& src,TargetState& tgt)
    {
      return fsm.theIPCC.isConfigAcceptable(evt.m_ConfigMsg);
    }
    template <class EVT,class FSM,class SourceState,class TargetState>
    bool cc_fsm_::NotAcceptableConfig::operator()(EVT const& evt,FSM& fsm,SourceState& src,TargetState& tgt)
    {
      return true;
    }
    template <class FSM,class SourceState,class TargetState>
    bool cc_fsm_::NotAcceptableConfig::operator()(EvContenLost const& evt, FSM& fsm,SourceState& src,TargetState& tgt)
    {
      return !fsm.theIPCC.isConfigAcceptable(evt.m_ConfigMsg);
    }
    // Replaces the default no-transition response.
    template <class FSM,class Event>
    void cc_fsm_::no_transition(Event const& e, FSM&, int state)
    {
      std::cout << "no transition from state " << state
                << " on event " << typeid(e).name() << std::endl;
    }

    // Pick a back-end
    // typedef msm::back::state_machine<cc_fsm_> cc_fsm;
    struct FSM_IPCC::FsmIpccImpl : public msm::back::state_machine<cc_fsm_>
    {
      explicit FsmIpccImpl(IpccFsmInvokeIF&  ipcc)
       : msm::back::state_machine<cc_fsm_>(boost::ref(ipcc))
      {
      }
    };

    FSM_IPCC::~FSM_IPCC() = default;
    FSM_IPCC::FSM_IPCC(
      IpccFsmInvokeIF&  ipcc)
    : theFSMImpl(new FsmIpccImpl(ipcc))
    {
    }
    bool FSM_IPCC::start()
    {
      if (theFSMImpl)
      {
        theFSMImpl->start();
        return true;
      }
      return false;
    }
    bool FSM_IPCC::stop()
    {
      if (theFSMImpl)
      {
        theFSMImpl->stop();
        return true;
      }
      return false;
    }
    boost::optional<const lmp::cc::appl::State&> FSM_IPCC::getActiveState() const
    {
      if (theFSMImpl)
      {
        //std::cout << "visit active state" << std::endl;
        SomeVisitor  visitor;
        theFSMImpl->visit_current_states(boost::ref(visitor));
        return visitor.theActiveState;
      }
      return boost::optional<const lmp::cc::appl::State&>();
    }
    template <class Event>
    bool FSM_IPCC::process_event(const Event& e)
    {
      if (theFSMImpl)
      {
        // std::cout << "FSM process event " << typeid(e).name() << std::endl;
        theFSMImpl->process_event(e);
        return true;
      }
      return false;
    }
    template bool FSM_IPCC::process_event(const EvBringUp&);
    template bool FSM_IPCC::process_event(const EvCCDn&);
    template bool FSM_IPCC::process_event(const EvConfDone&);
    template bool FSM_IPCC::process_event(const EvConfErr&);
    template bool FSM_IPCC::process_event(const EvNewConfOK&);
    template bool FSM_IPCC::process_event(const EvNewConfErr&);
    template bool FSM_IPCC::process_event(const EvContenWin&);
    template bool FSM_IPCC::process_event(const EvContenLost&);
    template bool FSM_IPCC::process_event(const EvAdminDown&);
    template bool FSM_IPCC::process_event(const EvNbrGoesDn&);
    template bool FSM_IPCC::process_event(const EvHelloRcvd&);
    template bool FSM_IPCC::process_event(const EvHoldTimer&);
    template bool FSM_IPCC::process_event(const EvSeqNumErr&);
    template bool FSM_IPCC::process_event(const EvReconfig&);
    template bool FSM_IPCC::process_event(const EvConfRet&);
    template bool FSM_IPCC::process_event(const EvHelloRet&);
    template bool FSM_IPCC::process_event(const EvDownTimer&);

  } // namespace cc
} // namespace lmp
