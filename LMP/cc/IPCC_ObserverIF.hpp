#ifndef LIBS_IPCC_OBSERVERIF_HPP_
#define LIBS_IPCC_OBSERVERIF_HPP_
/*
 * IPCC_ObserverIF.hpp
 *
 *  Created on: 11.03.2015
 *      Author: tom
 */
#include "base/ProtocolTypes.hpp"             // for DWORD

namespace lmp
{
  namespace cc
  {
    class IpccApplicationIF;

    namespace appl
    {
      class State;
      class Event;
      class Action;
      class IpccObserverIF
      {
      public:
        inline void notifyTransition(
          const IpccApplicationIF&  ipcc,
          const appl::State&        sourceState,
          const appl::Event&        event,
          const appl::State&        targetState,
          const appl::Action&       action)
        {  do_notifyTransition(ipcc, sourceState, event, targetState, action); }
        inline void notifyPeerIpccDiscovered(
          const IpccApplicationIF&  ipcc,
          lmp::DWORD                remoteNodeId,
          lmp::DWORD                remoteCCId)
        { do_notifyPeerIpccDiscovered(ipcc, remoteNodeId, remoteCCId); }
        virtual ~IpccObserverIF(){}
      private:
        virtual void do_notifyTransition(
          const IpccApplicationIF&  ipcc,
          const appl::State&        sourceState,
          const appl::Event&        event,
          const appl::State&        targetState,
          const appl::Action&       action) = 0;
        virtual void do_notifyPeerIpccDiscovered(
          const IpccApplicationIF&  ipcc,
          lmp::DWORD                remoteNodeId,
          lmp::DWORD                remoteCCId) = 0;
      };
    } // namespace appl
  } // namespace cc
} // namespace lmp


#endif /* LIBS_IPCC_OBSERVERIF_HPP_ */
