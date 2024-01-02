#include <Mgt_IPCCAdjacencyObserver.hpp>
#include <iostream>

namespace lmp_ipcc_adjacency_observer
{

IPCCAdjacencyObserver_i::IPCCAdjacencyObserver_i(
  CORBA::ORB_ptr           orb,
  PortableServer::POA_ptr  poa)
: theORB(CORBA::ORB::_duplicate(orb)),
  thePOA(PortableServer::POA::_duplicate(poa))
{
  //PortableServer::ObjectId *oid=thePOA->activate_object(this); delete oid;
}

IPCCAdjacencyObserver_i::~IPCCAdjacencyObserver_i()
{
  CORBA::release(thePOA);
  CORBA::release(theORB);
}

void IPCCAdjacencyObserver_i::destroy()
{
  PortableServer::ObjectId* oid=thePOA->servant_to_id(this);
  std::cout << "before deactivate_object" << std::endl;
  thePOA->deactivate_object(*oid);  delete oid;
  std::cout << "after deactivate_object" << std::endl;
  // _remove_ref(); // delete this;
}

void IPCCAdjacencyObserver_i::ipccAdjacencyAdded(
   ::lmp_ipcc::IPCC_ptr aIPCC)
{
  std::cout << "ipccAdjacencyObserver.ipccAdjacencyAdded("
            << aIPCC->getLocalCCId() << ", "
            << aIPCC->getRemoteAddress() << ", "
            << aIPCC->getRemotePortNumber() << ")" << std::endl;
}

void IPCCAdjacencyObserver_i::ipccAdjacencyRemoved(
  ::lmp_ipcc::IPCC_ptr aIPCC)
{
  std::cout << "ipccAdjacencyObserver.ipccAdjacencyRemoved("
            << aIPCC->getLocalCCId() << ", "
            << aIPCC->getRemoteAddress() << ", "
            << aIPCC->getRemotePortNumber() << ")" << std::endl;
}

} // end namespace lmp_ipcc_adjacency_observer

