/*
 * IPCC_Impl.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "Test_IPCC_Observer.hpp"
#include "IPCC_Impl.hpp"
#include "IPCC_ObserverIF.hpp"  // for operator<<, State, Action, Event, etc
#include <iostream>             // for operator<<, ostream, basic_ostream, etc
#include <typeinfo>             // for bad_cast

namespace lmp
{
  namespace cc
  {
    namespace appl
    {
      TestIpccObserver::TestIpccObserver(
        IpccImpl&  ipcc)
      : theIpcc(ipcc)
      {
        theIpcc.registerObserver(*this);
      }
      TestIpccObserver::~TestIpccObserver()
      {
    	theIpcc.deregisterObserver(*this);
      }
      const TestIpccObserver::TransistionSequence& TestIpccObserver::getTransistions() const
      {
        return theTransitions;
      }
      void TestIpccObserver::reset()
      {
        theTransitions.clear();
      }
      void TestIpccObserver::do_notifyTransition(
        const cc::IpccApplicationIF&  ipcc,
        const appl::State&            sourceState,
        const appl::Event&            event,
        const appl::State&            targetState,
        const appl::Action&           action)
      {
        std::cout << "IPCC[" << theIpcc.getLocalCCId() << "]." << event << ": "
                  << sourceState << " -> " << targetState
                  << " executing " << action << std::endl;
    	TransRecord  transRecord(sourceState.getType(),
    	                         event.getType(),
    	                         targetState.getType(),
    	                         action.getType());
    	theTransitions.push_back(transRecord);
      }
      void TestIpccObserver::do_notifyPeerIpccDiscovered(
        const cc::IpccApplicationIF&  ipcc,
        lmp::DWORD                    remoteNodeId,
        lmp::DWORD                    remoteCCId)
      {
        std::cout << "IPCC[" << ipcc.getLocalCCId() << "].notifyPeerIpccDiscovered("
                  << remoteNodeId << ", " << remoteCCId << ")" << std::endl;

      }

      TestIpccObserver::TransRecord::TransRecord(
        appl::State::Type         sourceState,
        appl::Event::EvType       event,
        appl::State::Type         targetState,
        appl::Action::ActionType  action)
      : theSourceState(sourceState),
        theEvent(event),
        theTargetState(targetState),
        theAction(action)
      {
      }
      bool TestIpccObserver::TransRecord::operator==(
        const TransRecord&  other) const
      {
        return
          ( theSourceState == other.theSourceState &&
            theEvent == other.theEvent &&
            theTargetState == other.theTargetState &&
            theAction == other.theAction );
      }
      std::ostream& operator<<(
        std::ostream&                                 os,
        const TestIpccObserver::TransistionSequence&  transitions)
      {
    	for (TestIpccObserver::TransistionSequence::const_iterator iter = transitions.begin(),
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
        const TestIpccObserver::TransRecord&          transition)
      {
    	os << transition.theEvent << "("
    	   << transition.theSourceState << "->"
    	   << transition.theTargetState << ")."
    	   << transition.theAction;
    	return os;
      }
    } // namespace appl
  } // namespace cc
} // namespace lmp
