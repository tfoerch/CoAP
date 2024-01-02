#ifndef LIBS_Neighbor_FACTORYIF_HPP_
#define LIBS_Neighbor_FACTORYIF_HPP_
/*
 * NeighborFactoryIF.hpp
 *
 *  Created on: 11.03.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"                  // for DWORD

namespace lmp
{
  namespace neighbor
  {
    class NeighborApplicationIF;

    class NeighborFactoryIF
    {
    public:
      inline NeighborApplicationIF const* getNeighbor(
        lmp::DWORD  neighborNodeId) const
      { return do_getNeighbor(neighborNodeId); }
      inline NeighborApplicationIF* accessNeighbor(
        lmp::DWORD  neighborNodeId)
      { return do_accessNeighbor(neighborNodeId); }
      inline NeighborApplicationIF* createNeighbor(
        lmp::DWORD              neighborNodeId)
      { return do_createNeighbor(neighborNodeId); }
      inline bool removeNeighbor(
        lmp::DWORD              neighborNodeId)
      { return do_removeNeighbor(neighborNodeId); }
      virtual ~NeighborFactoryIF(){}
    private:
      virtual NeighborApplicationIF const* do_getNeighbor(
        lmp::DWORD  neighborNodeId) const = 0;
      virtual NeighborApplicationIF* do_accessNeighbor(
        lmp::DWORD  neighborNodeId) = 0;
      virtual NeighborApplicationIF* do_createNeighbor(
        lmp::DWORD              neighborNodeId) = 0;
      virtual bool do_removeNeighbor(
        lmp::DWORD              neighborNodeId) = 0;
    };
  } // namespace neighbor
} // namespace lmp


#endif /* LIBS_Neighbor_FACTORYIF_HPP_ */
