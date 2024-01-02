/*
 * Neighbor.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "Neighbor.hpp"
#include "cc/IPCCApplicationIF.hpp"
#include "cc/IPCC_State.hpp"
#include "cc/IPCC_Event.hpp"
#include "cc/IPCC_Action.hpp"
#include <typeinfo>             // for bad_cast

namespace lmp
{
  namespace neighbor
  {
    Neighbor::Neighbor(
      lmp::DWORD                       nodeId)
      : m_nodeId(nodeId)
    {
    }
    void Neighbor::do_enable()
    {
    }
    void Neighbor::do_disable()
    {
    }
    lmp::DWORD Neighbor::do_getNodeId() const
    {
      return m_nodeId;
    }
    void Neighbor::do_ipccAdjacencyAdded(
      cc::IpccApplicationIF&   ipcc)
    {
      std::cout << "Neighbor[" << m_nodeId << "].ipccAdjacencyAdded("
                << ipcc.getLocalCCId() << ")" << std::endl;
      ipcc.registerObserver(*this);
    }
    void Neighbor::do_ipccAdjacencyRemoved(
      cc::IpccApplicationIF&   ipcc)
    {
      std::cout << "Neighbor[" << m_nodeId << "].ipccAdjacencyRemoved("
                << ipcc.getLocalCCId() << ")" << std::endl;
      ipcc.deregisterObserver(*this);
    }
    void Neighbor::do_notifyTransition(
      const cc::IpccApplicationIF&  ipcc,
      const cc::appl::State&        sourceState,
      const cc::appl::Event&        event,
      const cc::appl::State&        targetState,
      const cc::appl::Action&       action)
    {
      std::cout << "Neighbor[" << m_nodeId << "].IPCC[" << ipcc.getLocalCCId() << "]."
                << event << ": " << sourceState << " -> " << targetState
                << " executing " << action << std::endl;

    }
    void Neighbor::do_notifyPeerIpccDiscovered(
      const cc::IpccApplicationIF&  ipcc,
      lmp::DWORD                    remoteNodeId,
      lmp::DWORD                    remoteCCId)
    {
      std::cout << "Neighbor[" << m_nodeId << "].IPCC[" << ipcc.getLocalCCId() << "].notifyPeerIpccDiscovered("
                << remoteNodeId << ", " << remoteCCId << ")" << std::endl;

    }

  } // namespace neighbor
} // namespace lmp
