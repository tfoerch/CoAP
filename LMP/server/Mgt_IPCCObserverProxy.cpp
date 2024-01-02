
#include <Mgt_IPCCObserverProxy.hpp>
#include <Mgt_IPCC.hpp>
#include <iostream>                     // for operator<<, ostream, etc
#include <typeinfo>                     // for bad_cast


namespace lmp_ipcc
{
  IpccObserverProxy::IpccObserverProxy(
    lmp_ipcc::IPCC_i&             ipcc,
    const IPCCObserverContainer&  ipccObserverContainer)
  : m_ipcc(ipcc),
    m_ipccObserverContainer(ipccObserverContainer),
    m_transitions()
  {
  }
  const IpccObserverProxy::TransistionSequence& IpccObserverProxy::getTransistions() const
  {
    return m_transitions;
  }
  void IpccObserverProxy::reset()
  {
    m_transitions.clear();
  }
  void IpccObserverProxy::do_notifyTransition(
    const lmp::cc::IpccApplicationIF&  ipcc,
    const lmp::cc::appl::State&        sourceState,
    const lmp::cc::appl::Event&        event,
    const lmp::cc::appl::State&        targetState,
    const lmp::cc::appl::Action&       action)
  {
    std::cout << "IPCC[" << m_ipcc.getLocalCCId() << "].notifyTransition: " << event << ": "
              << sourceState << " -> " << targetState
              << " executing " << action << std::endl;
    TransRecord  transRecord(sourceState.getType(),
                             event.getType(),
                             targetState.getType(),
                             action.getType());
    m_transitions.push_back(transRecord);
    lmp_ipcc::IPCC_var ipccRef = m_ipcc._this();
    for (IPCCObserverContainer::const_iterator iter = m_ipccObserverContainer.begin(),
                                               end_iter = m_ipccObserverContainer.end();
         iter != end_iter;
         ++iter)
    {
      (*iter)->eventProcessed(ipccRef,
                              convert(event),
                              convert(sourceState),
                              convert(targetState),
                              convert(action));
    }
  }
  void IpccObserverProxy::do_notifyPeerIpccDiscovered(
    const lmp::cc::IpccApplicationIF&  ipcc,
    lmp::DWORD                         remoteNodeId,
    lmp::DWORD                         remoteCCId)
  {
    std::cout << "IPCC[" << m_ipcc.getLocalCCId() << "].notifyPeerIpccDiscovered("
              << remoteNodeId << ", " << remoteCCId << ")" << std::endl;
    lmp_ipcc::IPCC_var ipccRef = m_ipcc._this();
    for (IPCCObserverContainer::const_iterator iter = m_ipccObserverContainer.begin(),
                                               end_iter = m_ipccObserverContainer.end();
         iter != end_iter;
         ++iter)
    {
      (*iter)->peerIpccDiscovered(ipccRef,
                                  remoteNodeId,
                                  remoteCCId);
    }
  }

  ::lmp_ipcc_common::IPCC_State IpccObserverProxy::convert(
    const lmp::cc::appl::State&         state)
  {
    ::lmp_ipcc_common::IPCC_State observerState = ::lmp_ipcc_common::IPCC_Down;
    switch(state.getType())
    {
      case lmp::cc::appl::State::Down:
        observerState = ::lmp_ipcc_common::IPCC_Down;
        break;
      case lmp::cc::appl::State::ConfSnd:
        observerState = ::lmp_ipcc_common::IPCC_ConfSend;
        break;
      case lmp::cc::appl::State::ConfRcv:
        observerState = ::lmp_ipcc_common::IPCC_ConfRecv;
        break;
      case lmp::cc::appl::State::Active:
        observerState = ::lmp_ipcc_common::IPCC_Active;
        break;
      case lmp::cc::appl::State::Up:
        observerState = ::lmp_ipcc_common::IPCC_Up;
        break;
      case lmp::cc::appl::State::GoingDown:
        observerState = ::lmp_ipcc_common::IPCC_GoingDown;
        break;
    }
    return observerState;
  }
  ::lmp_ipcc_observer::IPCC_Event IpccObserverProxy::convert(
    const lmp::cc::appl::Event&         event)
  {
    ::lmp_ipcc_observer::IPCC_Event observerEvent = ::lmp_ipcc_observer::EvBringUp;
    switch(event.getType())
    {
      case lmp::cc::appl::Event::EvBringUp:
        observerEvent = ::lmp_ipcc_observer::EvBringUp;
        break;
      case lmp::cc::appl::Event::EvCCDn:
        observerEvent = ::lmp_ipcc_observer::EvCCDn;
        break;
      case lmp::cc::appl::Event::EvConfDone:
        observerEvent = ::lmp_ipcc_observer::EvConfDone;
        break;
      case lmp::cc::appl::Event::EvConfErr:
        observerEvent = ::lmp_ipcc_observer::EvConfErr;
        break;
      case lmp::cc::appl::Event::EvNewConfOK:
        observerEvent = ::lmp_ipcc_observer::EvNewConfOK;
        break;
      case lmp::cc::appl::Event::EvNewConfErr:
        observerEvent = ::lmp_ipcc_observer::EvNewConfErr;
        break;
      case lmp::cc::appl::Event::EvContenWin:
        observerEvent = ::lmp_ipcc_observer::EvContenWin;
        break;
      case lmp::cc::appl::Event::EvContenLost:
        observerEvent = ::lmp_ipcc_observer::EvContenLost;
        break;
      case lmp::cc::appl::Event::EvAdminDown:
        observerEvent = ::lmp_ipcc_observer::EvAdminDown;
        break;
      case lmp::cc::appl::Event::EvNbrGoesDn:
        observerEvent = ::lmp_ipcc_observer::EvNbrGoesDn;
        break;
      case lmp::cc::appl::Event::EvHelloRcvd:
        observerEvent = ::lmp_ipcc_observer::EvHelloRcvd;
        break;
      case lmp::cc::appl::Event::EvHoldTimer:
        observerEvent = ::lmp_ipcc_observer::EvHoldTimer;
        break;
      case lmp::cc::appl::Event::EvSeqNumErr:
        observerEvent = ::lmp_ipcc_observer::EvSeqNumErr;
        break;
      case lmp::cc::appl::Event::EvReconfig:
        observerEvent = ::lmp_ipcc_observer::EvReconfig;
        break;
      case lmp::cc::appl::Event::EvConfRet:
        observerEvent = ::lmp_ipcc_observer::EvConfRet;
        break;
      case lmp::cc::appl::Event::EvHelloRet:
        observerEvent = ::lmp_ipcc_observer::EvHelloRet;
        break;
      case lmp::cc::appl::Event::EvDownTimer:
        observerEvent = ::lmp_ipcc_observer::EvDownTimer;
        break;
    }
    return observerEvent;
  }
  ::lmp_ipcc_observer::IPCC_Action IpccObserverProxy::convert(
    const lmp::cc::appl::Action&        action)
  {
    ::lmp_ipcc_observer::IPCC_Action observerAction = ::lmp_ipcc_observer::ActionNoAction;
    switch (action.getType())
    {
      case lmp::cc::appl::Action::ActionSendConfig:
        observerAction = ::lmp_ipcc_observer::ActionSendConfig;
        break;
      case lmp::cc::appl::Action::ActionStopSendConfig:
        observerAction = ::lmp_ipcc_observer::ActionStopSendConfig;
        break;
      case lmp::cc::appl::Action::ActionResendConfig:
        observerAction = ::lmp_ipcc_observer::ActionResendConfig;
        break;
      case lmp::cc::appl::Action::ActionSendConfigAck:
        observerAction = ::lmp_ipcc_observer::ActionSendConfigAck;
        break;
      case lmp::cc::appl::Action::ActionSendConfigNack:
        observerAction = ::lmp_ipcc_observer::ActionSendConfigNack;
        break;
      case lmp::cc::appl::Action::ActionSendHello:
        observerAction = ::lmp_ipcc_observer::ActionSendHello;
        break;
      case lmp::cc::appl::Action::ActionStopSendHello:
        observerAction = ::lmp_ipcc_observer::ActionStopSendHello;
        break;
      case lmp::cc::appl::Action::ActionSetCCDownFlag:
        observerAction = ::lmp_ipcc_observer::ActionSetCCDownFlag;
        break;
      case lmp::cc::appl::Action::ActionClearCCDownFlag:
        observerAction = ::lmp_ipcc_observer::ActionClearCCDownFlag;
        break;
      case lmp::cc::appl::Action::ActionNoAction:
        observerAction = ::lmp_ipcc_observer::ActionNoAction;
        break;
    }
    return observerAction;
  }


  IpccObserverProxy::TransRecord::TransRecord(
    lmp::cc::appl::State::Type         sourceState,
    lmp::cc::appl::Event::EvType       event,
    lmp::cc::appl::State::Type         targetState,
    lmp::cc::appl::Action::ActionType  action)
  : m_sourceState(sourceState),
    m_event(event),
    m_targetState(targetState),
    m_action(action)
  {
  }
  bool IpccObserverProxy::TransRecord::operator==(
    const TransRecord&  other) const
  {
    return
      ( m_sourceState == other.m_sourceState &&
        m_event == other.m_event &&
        m_targetState == other.m_targetState &&
        m_action == other.m_action );
  }
  std::ostream& operator<<(
    std::ostream&                                 os,
    const IpccObserverProxy::TransistionSequence&  transitions)
  {
    for (IpccObserverProxy::TransistionSequence::const_iterator iter = transitions.begin(),
                                                                end_iter = transitions.end();
         iter != end_iter;
         ++iter)
    {
      if (iter != transitions.begin())
      {
        os << ", ";
      }
      os << *iter;
    }
    return os;
  }
  std::ostream& operator<<(
    std::ostream&                                 os,
    const IpccObserverProxy::TransRecord&         transition)
  {
    os << transition.m_event << "("
       << transition.m_sourceState << "->"
       << transition.m_targetState << ")."
       << transition.m_action;
    return os;
  }
} // namespace lmp
