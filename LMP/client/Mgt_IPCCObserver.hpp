#include <lmp_mgtif_ipcc_observer.hpp>

#include <omniORB4/CORBA.h>              // for ORB_ptr
#include <omniORB4/poa.h>                // for POA_ptr, etc
#include <iostream>
#include <deque>

namespace lmp_ipcc_observer
{

class IPCCObserver_i : public POA_lmp_ipcc_observer::IPCCObserver,
                       public virtual PortableServer::RefCountServantBase
{
public:
  struct EventProcRecord
  {
    ::CORBA::Long                     localNodeId;
    ::CORBA::Long                     localCCId;
    ::lmp_ipcc_observer::IPCC_Event   event;
    ::lmp_ipcc_common::IPCC_State     sourceState;
    ::lmp_ipcc_common::IPCC_State     targetState;
    ::lmp_ipcc_observer::IPCC_Action  action;
  };
  typedef  std::deque<EventProcRecord>  EventProcSequence;
  IPCCObserver_i(
    CORBA::ORB_ptr           orb,
    PortableServer::POA_ptr  poa);
  virtual ~IPCCObserver_i();
  virtual void destroy();
  virtual void eventProcessed(
    ::lmp_ipcc::IPCC_ptr              aIPCC,
    ::lmp_ipcc_observer::IPCC_Event   event,
    ::lmp_ipcc_common::IPCC_State     sourceState,
    ::lmp_ipcc_common::IPCC_State     targetState,
    ::lmp_ipcc_observer::IPCC_Action  action);
  virtual void peerIpccDiscovered(
    ::lmp_ipcc::IPCC_ptr              aIPCC,
    ::CORBA::Long                     remoteNodeId,
    ::CORBA::Long                     remoteCCId);
private:

  CORBA::ORB_ptr           theORB;
  PortableServer::POA_ptr  thePOA;
  EventProcSequence        m_eventProcSequence;
};

std::ostream& operator<<(
  std::ostream&                     os,
  ::lmp_ipcc_observer::IPCC_Event   event);
std::ostream& operator<<(
  std::ostream&                     os,
  ::lmp_ipcc_common::IPCC_State     state);
std::ostream& operator<<(
  std::ostream&                     os,
  ::lmp_ipcc_observer::IPCC_Action  action);

} // end namespace lmp_ipcc_observer
