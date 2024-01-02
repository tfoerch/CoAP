#ifndef LIBS_IPCC_ADJACENCYOBSERVERIF_HPP_
#define LIBS_IPCC_ADJACENCYOBSERVERIF_HPP_
/*
 * IPCCAdjacencyObserverIF.hpp
 *
 *  Created on: 11.03.2015
 *      Author: tom
 */

namespace lmp
{
  namespace cc
  {
    class IpccApplicationIF;

    class IpccAdjacencyObserverIF
    {
    public:
      inline void ipccAdjacencyAdded(
        IpccApplicationIF&                     ipcc)
      {  do_ipccAdjacencyAdded(ipcc); }
      inline void ipccAdjacencyRemoved(
        IpccApplicationIF&                     ipcc)
      {  do_ipccAdjacencyRemoved(ipcc); }
      virtual ~IpccAdjacencyObserverIF(){}
    private:
      virtual void do_ipccAdjacencyAdded(
        IpccApplicationIF&                     ipcc) = 0;
      virtual void do_ipccAdjacencyRemoved(
        IpccApplicationIF&                     ipcc) = 0;
    };
  } // namespace cc
} // namespace lmp


#endif /* LIBS_IPCC_ADJACENCYOBSERVERIF_HPP_ */
