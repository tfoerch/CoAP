#ifndef LIBS_Node_HPP_
#define LIBS_Node_HPP_
/*
 * Node.hpp
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include "node/NodeApplicationIF.hpp"

#include <map>
#include <set>

namespace lmp
{
  namespace node
  {
    class Node : public NodeApplicationIF
    {
    public:
      explicit Node(
        lmp::DWORD                       nodeId);
      virtual ~Node(){}
    private:
      typedef std::map<lmp::DWORD, // nodeId
                       neighbor::NeighborApplicationIF*>  NeighborNodes;
      typedef std::set<lmp::DWORD>                        SetOfIdentifiers;
      // implement NeighborFactoryIF
      virtual neighbor::NeighborApplicationIF const* do_getNeighbor(
        lmp::DWORD              neighborNodeId) const;
      virtual neighbor::NeighborApplicationIF* do_accessNeighbor(
        lmp::DWORD              neighborNodeId);
      virtual neighbor::NeighborApplicationIF* do_createNeighbor(
        lmp::DWORD              neighborNodeId);
      virtual bool do_removeNeighbor(
        lmp::DWORD              neighborNodeId);
      // implement NeighbordjacencyObserverIF
      virtual void do_neighborAdjacencyAdded(
        lmp::DWORD              neighborNodeId,
        cc::IpccApplicationIF&  ipcc);
      virtual void do_neighborAdjacencyRemoved(
        lmp::DWORD              neighborNodeId,
        cc::IpccApplicationIF&  ipcc);
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

      lmp::DWORD                  m_nodeId;
      NeighborNodes               m_neighborNodes;
      SetOfIdentifiers            m_assignedLocalCCIds;
    };
  } // namespace node
} // namespace lmp

#endif /* LIBS_Node_HPP_ */
