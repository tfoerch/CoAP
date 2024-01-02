#include <lmp_mgtif_neighbor_adjacency_observer.hpp>
#include <lmp_mgtif_neighbor.hpp>

#include <omniORB4/CORBA.h>              // for ORB_ptr
#include <omniORB4/poa.h>                    // for POA_ptr, etc

namespace lmp_neighbor_adjacency_observer
{

class NeighborAdjacencyObserver_i : public POA_lmp_neighbor_adjacency_observer::NeighborAdjacencyObserver,
                                    public virtual PortableServer::RefCountServantBase
{
public:
  NeighborAdjacencyObserver_i(
    CORBA::ORB_ptr           orb,
    PortableServer::POA_ptr  poa);
  virtual ~NeighborAdjacencyObserver_i();
  virtual void destroy();
  virtual void neighborAdjacencyAdded(
    ::lmp_neighbor::Neighbor_ptr aNeighbor);
  virtual void neighborAdjacencyRemoved(
    ::lmp_neighbor::Neighbor_ptr aNeighbor);
private:

  CORBA::ORB_ptr           theORB;
  PortableServer::POA_ptr  thePOA;
};

} // end namespace lmp_neighbor_adjacency_observer
