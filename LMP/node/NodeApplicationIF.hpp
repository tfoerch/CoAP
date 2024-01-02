#ifndef LIBS_Node_ApplicationIF_HPP_
#define LIBS_Node_ApplicationIF_HPP_
/*
 * NodeApplicationIF.hpp
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include "neighbor/NeighborFactoryIF.hpp"
#include "neighbor/NeighborAdjacencyObserverIF.hpp"
#include "node/NodeLocalCCIdPoolIF.hpp"

namespace lmp
{
  namespace node
  {
    class NodeApplicationIF : public neighbor::NeighborFactoryIF,
                              public neighbor::NeighborAdjacencyObserverIF,
                              public NodeLocalCCIdPoolIF
    {
    public:
      inline void enable()
      { do_enable(); }
      inline void disable()
      { do_disable(); }
      inline lmp::DWORD getNodeId() const
      { return do_getNodeId(); }
      virtual ~NodeApplicationIF(){}
   private:
      virtual void do_enable() = 0;
      virtual void do_disable() = 0;
      virtual lmp::DWORD do_getNodeId() const = 0;
    };
  } // namespace node
} // namespace lmp

#endif /* LIBS_Node_ApplicationIF_HPP_ */
