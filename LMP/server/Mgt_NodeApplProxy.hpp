#ifndef Server_Node_Proxy_HPP_
#define Server_Node_Proxy_HPP_
/*
 * Mgt_NodeApplProxy.hpp
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include "node/NodeApplicationIF.hpp"
#include <lmp_mgtif_node.hpp>
#include <Mgt_NeighborAdjacencyChangeFtorIF.hpp>

namespace lmp_node
{
  class NeighborAdjacencyChangeFtorIF;

  class NodeApplProxy : public lmp::node::NodeApplicationIF
  {
  public:
    NodeApplProxy(
      lmp::node::NodeApplicationIF&   node,
      NeighborAdjacencyChangeFtorIF&  neighborAdjAddedFtor,
      NeighborAdjacencyChangeFtorIF&  neighborAdjRemovedFtor);
    virtual ~NodeApplProxy(){}
    inline lmp::node::NodeApplicationIF& getNode()
    { return m_node; }
  private:
    // implement NeighborFactoryIF
    virtual lmp::neighbor::NeighborApplicationIF const* do_getNeighbor(
      lmp::DWORD  neighborNodeId) const;
    virtual lmp::neighbor::NeighborApplicationIF* do_accessNeighbor(
      lmp::DWORD  neighborNodeId);
    virtual lmp::neighbor::NeighborApplicationIF* do_createNeighbor(
      lmp::DWORD                   neighborNodeId);
    virtual bool do_removeNeighbor(
      lmp::DWORD                   neighborNodeId);
    // implement NeighbordjacencyObserverIF
    virtual void do_neighborAdjacencyAdded(
      lmp::DWORD                   neighborNodeId,
      lmp::cc::IpccApplicationIF&  ipcc);
    virtual void do_neighborAdjacencyRemoved(
      lmp::DWORD                   neighborNodeId,
      lmp::cc::IpccApplicationIF&  ipcc);
    // implement NodeLocalCCIdPoolIF
    virtual lmp::DWORD do_registerFreeLocalCCId();
    virtual bool do_checkLocalCCId(
      lmp::DWORD localCCId) const;
    virtual bool do_registerLocalCCId(
      lmp::DWORD localCCId);
    virtual bool do_releaseLocalCCId(
      lmp::DWORD localCCId);
    // implement NodeApplicationIF
    virtual void do_enable();
    virtual void do_disable();
    virtual lmp::DWORD do_getNodeId() const;

    lmp::node::NodeApplicationIF&   m_node;
    NeighborAdjacencyChangeFtorIF&  m_neighborAdjAddedFtor;
    NeighborAdjacencyChangeFtorIF&  m_neighborAdjRemovedFtor;
  };

} // end namespace LMP

#endif /* Server_Node_Proxy_HPP_ */
