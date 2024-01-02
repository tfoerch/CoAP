#include <Mgt_NodeApplProxy.hpp>
#include "cc/IPCCAdjacencyObserverIF.hpp"
#include "neighbor/NeighborApplicationIF.hpp"
#include <iostream>

namespace lmp_node
{
  NodeApplProxy::NodeApplProxy(
    lmp::node::NodeApplicationIF&   node,
    NeighborAdjacencyChangeFtorIF&  neighborAdjAddedFtor,
    NeighborAdjacencyChangeFtorIF&  neighborAdjRemovedFtor)
  : m_node(node),
    m_neighborAdjAddedFtor(neighborAdjAddedFtor),
    m_neighborAdjRemovedFtor(neighborAdjRemovedFtor)
  {
  }

  void NodeApplProxy::do_enable()
  {
    m_node.enable();
  }
  void NodeApplProxy::do_disable()
  {
    m_node.disable();
  }
  lmp::DWORD NodeApplProxy::do_getNodeId() const
  {
    return m_node.getNodeId();
  }
  lmp::neighbor::NeighborApplicationIF const* NodeApplProxy::do_getNeighbor(
    lmp::DWORD  neighborNodeId) const
  {
    return m_node.getNeighbor(neighborNodeId);
  }
  lmp::neighbor::NeighborApplicationIF* NodeApplProxy::do_accessNeighbor(
    lmp::DWORD  neighborNodeId)
  {
    return m_node.accessNeighbor(neighborNodeId);
  }
  lmp::neighbor::NeighborApplicationIF* NodeApplProxy::do_createNeighbor(
    lmp::DWORD                   neighborNodeId)
  {
    return m_node.createNeighbor(neighborNodeId);
  }
  bool NodeApplProxy::do_removeNeighbor(
    lmp::DWORD                   neighborNodeId)
  {
    return m_node.removeNeighbor(neighborNodeId);
  }
  void NodeApplProxy::do_neighborAdjacencyAdded(
    lmp::DWORD                   neighborNodeId,
    lmp::cc::IpccApplicationIF&  ipcc)
  {
    m_neighborAdjAddedFtor(neighborNodeId, ipcc);
    lmp::neighbor::NeighborApplicationIF* neighborPtr = accessNeighbor(neighborNodeId);
    if (neighborPtr)
    {
      lmp::cc::IpccAdjacencyObserverIF* ipccAdjObservPtr =
        dynamic_cast<lmp::cc::IpccAdjacencyObserverIF*>(neighborPtr);
      if (ipccAdjObservPtr)
      {
        ipccAdjObservPtr->ipccAdjacencyAdded(ipcc);
      }
      else
      {
        std::cout << "Node::do_neighborAdjacencyAdded() dynamic_cast failed" << std::endl;
      }
    }
  }

  void NodeApplProxy::do_neighborAdjacencyRemoved(
    lmp::DWORD                   neighborNodeId,
    lmp::cc::IpccApplicationIF&  ipcc)
  {
    m_neighborAdjRemovedFtor(neighborNodeId, ipcc);
  }

  lmp::DWORD NodeApplProxy::do_registerFreeLocalCCId()
  {
    return m_node.registerFreeLocalCCId();
  }
  bool NodeApplProxy::do_checkLocalCCId(
    lmp::DWORD localCCId) const
  {
    return m_node.isLocalCCIdFree(localCCId);
  }
  bool NodeApplProxy::do_registerLocalCCId(
    lmp::DWORD localCCId)
  {
    return m_node.registerLocalCCId(localCCId);
  }
  bool NodeApplProxy::do_releaseLocalCCId(
    lmp::DWORD localCCId)
  {
    return m_node.releaseLocalCCId(localCCId);
  }


} // end namespace lmp_node
