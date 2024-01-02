#ifndef IPCC_OBSERVER_PROXY_HPP_
#define IPCC_OBSERVER_PROXY_HPP_
/*
 * Mgt_IPCCObserverProxy.hpp
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include <IPCC_ObserverIF.hpp>
#include "cc/IPCC_State.hpp"
#include "cc/IPCC_Event.hpp"
#include "cc/IPCC_Action.hpp"
#include <lmp_mgtif_ipcc_observer.hpp>

#include <deque>
#include <set>
#include <iosfwd>                       // for ostream

namespace lmp_ipcc
{
  class IPCC_i;
  class IpccObserverProxy : public lmp::cc::appl::IpccObserverIF
  {
  public:
    struct TransRecord
    {
      TransRecord(
        lmp::cc::appl::State::Type         sourceState,
    	lmp::cc::appl::Event::EvType       event,
    	lmp::cc::appl::State::Type         targetState,
    	lmp::cc::appl::Action::ActionType  action);
      bool operator==(
        const TransRecord&  other) const;
      lmp::cc::appl::State::Type         m_sourceState;
      lmp::cc::appl::Event::EvType       m_event;
      lmp::cc::appl::State::Type         m_targetState;
      lmp::cc::appl::Action::ActionType  m_action;
    };
    typedef  std::deque<TransRecord>  TransistionSequence;
    typedef  std::set<::lmp_ipcc_observer::IPCCObserver_var>   IPCCObserverContainer;
    IpccObserverProxy(
      lmp_ipcc::IPCC_i&                  ipcc,
      const IPCCObserverContainer&       ipccObserverContainer);
    const TransistionSequence& getTransistions() const;
    void reset();
    static ::lmp_ipcc_common::IPCC_State convert(
      const lmp::cc::appl::State&         state);
  private:
    virtual void do_notifyTransition(
      const lmp::cc::IpccApplicationIF&  ipcc,
      const lmp::cc::appl::State&        sourceState,
      const lmp::cc::appl::Event&        event,
      const lmp::cc::appl::State&        targetState,
      const lmp::cc::appl::Action&       action);
    virtual void do_notifyPeerIpccDiscovered(
      const lmp::cc::IpccApplicationIF&  ipcc,
      lmp::DWORD                         remoteNodeId,
      lmp::DWORD                         remoteCCId);
   static ::lmp_ipcc_observer::IPCC_Event convert(
     const lmp::cc::appl::Event&         event);
   static ::lmp_ipcc_observer::IPCC_Action convert(
     const lmp::cc::appl::Action&        action);
    lmp_ipcc::IPCC_i&                  m_ipcc;
    const IPCCObserverContainer&       m_ipccObserverContainer;
    TransistionSequence                m_transitions;
  };
  std::ostream& operator<<(
    std::ostream&                                  os,
    const IpccObserverProxy::TransistionSequence&  transitions);
  std::ostream& operator<<(
    std::ostream&                                  os,
    const IpccObserverProxy::TransRecord&          transition);
} // namespace lmp

#endif /* IPCC_OBSERVER_PROXY_HPP_ */
