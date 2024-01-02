#ifndef LIBS_Neighbor_ADJACENCYOBSERVERIF_HPP_
#define LIBS_Neighbor_ADJACENCYOBSERVERIF_HPP_
/*
 * NeighborAdjacencyObserverIF.hpp
 *
 *  Created on: 11.03.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"                  // for DWORD

namespace lmp
{
  namespace cc
  {
    class IpccApplicationIF;
  }
  namespace neighbor
  {
    class NeighborApplicationIF;

    class NeighborAdjacencyObserverIF
    {
    public:
      inline void neighborAdjacencyAdded(
        lmp::DWORD              neighborNodeId,
        cc::IpccApplicationIF&  ipcc)
      { do_neighborAdjacencyAdded(neighborNodeId, ipcc); }
      inline void neighborAdjacencyRemoved(
        lmp::DWORD              neighborNodeId,
        cc::IpccApplicationIF&  ipcc)
      { do_neighborAdjacencyRemoved(neighborNodeId, ipcc); }
      virtual ~NeighborAdjacencyObserverIF(){}
    private:
      virtual void do_neighborAdjacencyAdded(
        lmp::DWORD              neighborNodeId,
        cc::IpccApplicationIF&  ipcc) = 0;
      virtual void do_neighborAdjacencyRemoved(
        lmp::DWORD              neighborNodeId,
        cc::IpccApplicationIF&  ipcc) = 0;
    };
  } // namespace neighbor
} // namespace lmp


#endif /* LIBS_Neighbor_ADJACENCYOBSERVERIF_HPP_ */
