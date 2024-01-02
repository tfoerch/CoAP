#include <Mgt_NeighborAdjacencyObserver.hpp>
#include <iostream>

namespace lmp_neighbor_adjacency_observer
{

NeighborAdjacencyObserver_i::NeighborAdjacencyObserver_i(
  CORBA::ORB_ptr           orb,
  PortableServer::POA_ptr  poa)
: theORB(CORBA::ORB::_duplicate(orb)),
  thePOA(PortableServer::POA::_duplicate(poa))
{
  //PortableServer::ObjectId *oid=thePOA->activate_object(this); delete oid;
}

NeighborAdjacencyObserver_i::~NeighborAdjacencyObserver_i()
{
  CORBA::release(thePOA);
  CORBA::release(theORB);
}

void NeighborAdjacencyObserver_i::destroy()
{
  PortableServer::ObjectId* oid=thePOA->servant_to_id(this);
  std::cout << "before deactivate_object" << std::endl;
  thePOA->deactivate_object(*oid);  delete oid;
  std::cout << "after deactivate_object" << std::endl;
  // _remove_ref(); // delete this;
}

void NeighborAdjacencyObserver_i::neighborAdjacencyAdded(
   ::lmp_neighbor::Neighbor_ptr aNeighbor)
{
  std::cout << "neighborAdjacencyObserver["
            << /* localCCId << */ "].neighborAdjacencyAdded()" << std::endl;
}

void NeighborAdjacencyObserver_i::neighborAdjacencyRemoved(
  ::lmp_neighbor::Neighbor_ptr aNeighbor)
{
  std::cout << "neighborAdjacencyObserver["
            << /* localCCId << */ "].neighborAdjacencyAdded()" << std::endl;
}

} // end namespace lmp_neighbor_adjacency_observer

