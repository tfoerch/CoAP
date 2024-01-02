#ifndef Server_NeighborAdjacencyFtorIF_HPP_
#define Server_NeighborAdjacencyFtorIF_HPP_
/*
 * Mgt_NeighborAdjacencyChangeFtorIF.hpp
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"                  // for DWORD
namespace lmp
{
  namespace cc
  {
    class IpccApplicationIF;
  }
}

namespace lmp_node
{

  class NeighborAdjacencyChangeFtorIF
  {
  public:
    inline void operator()(
      lmp::DWORD                   neighborNodeId,
      lmp::cc::IpccApplicationIF&  ipcc)
    { do_process(neighborNodeId, ipcc); }
    virtual ~NeighborAdjacencyChangeFtorIF(){}
  private:
    virtual void do_process(
      lmp::DWORD                   neighborNodeId,
      lmp::cc::IpccApplicationIF&  ipcc) = 0;
  };

} // end namespace lmp_node

#endif /* Server_NeighborAdjacencyFtorIF_HPP_ */
