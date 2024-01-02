#ifndef LIBS_Neighbor_APPLICATIONIF_HPP_
#define LIBS_Neighbor_APPLICATIONIF_HPP_
/*
 * NeighborApplicationIF.hpp
 *
 *  Created on: 11.03.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"             // for DWORD

namespace lmp
{
  namespace neighbor
  {
    namespace appl
    {
      class NeighborObserverProxyIF;
    }
    class NeighborApplicationIF
    {
    public:
      inline void enable()
      { do_enable(); }
      inline void disable()
      { do_disable(); }
      inline lmp::DWORD getNodeId() const
      { return do_getNodeId(); }
      virtual ~NeighborApplicationIF(){}
    private:
      virtual void do_enable() = 0;
      virtual void do_disable() = 0;
      virtual lmp::DWORD do_getNodeId() const = 0;
    };
  } // namespace neighbor
} // namespace lmp


#endif /* LIBS_Neighbor_APPLICATIONIF_HPP_ */
