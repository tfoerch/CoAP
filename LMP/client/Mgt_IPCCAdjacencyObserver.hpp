#include <lmp_mgtif_ipcc_adjacency_observer.hpp>
#include <lmp_mgtif_ipcc.hpp>

#include <omniORB4/CORBA.h>              // for ORB_ptr
#include <omniORB4/poa.h>                    // for POA_ptr, etc

namespace lmp_ipcc_adjacency_observer
{

class IPCCAdjacencyObserver_i : public POA_lmp_ipcc_adjacency_observer::IPCCAdjacencyObserver,
                                public virtual PortableServer::RefCountServantBase
{
public:
  IPCCAdjacencyObserver_i(
    CORBA::ORB_ptr           orb,
    PortableServer::POA_ptr  poa);
  virtual ~IPCCAdjacencyObserver_i();
  virtual void destroy();
  virtual void ipccAdjacencyAdded(
    ::lmp_ipcc::IPCC_ptr aIPCC);
  virtual void ipccAdjacencyRemoved(
    ::lmp_ipcc::IPCC_ptr aIPCC);
private:

  CORBA::ORB_ptr           theORB;
  PortableServer::POA_ptr  thePOA;
};

} // end namespace lmp_ipcc_adjacency_observer
