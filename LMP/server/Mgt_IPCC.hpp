#include <lmp_mgtif_ipcc.hpp>
#include <lmp_mgtif_ipcc_observer.hpp>
#include <lmp_mgtif_node.hpp>
#include <Mgt_NodeApplProxy.hpp>
#include <Mgt_NetworkIFProxy.hpp>
#include <Mgt_IPCCObserverProxy.hpp>
#include "cc/UDP_Msg_Handler.hpp"
#include "cc/IPCC_Impl.hpp"
#include "cc/IPCC_ObserverIF.hpp"

#include <omniORB4/CORBA.h>  // for Long, Short
#include <omniORB4/poa.h>    // for POA_ptr

namespace lmp_node
{
  class NodeApplProxy;
}
namespace lmp_netif
{
  class IPCCInDestructionFtorIF;
}

namespace lmp_ipcc
{
  class IPCC_i : public POA_lmp_ipcc::IPCC
  {
  public:
    IPCC_i(
      PortableServer::POA_ptr              poa,
      lmp_node::NodeApplProxy&             node,
      lmp_netif::NetworkIFProxy&           networkIf,
      lmp::cc::IpccApplicationIF&          ipcc,
      lmp_netif::IPCCInDestructionFtorIF&  ipccInDestructionFtor);
    virtual ~IPCC_i();
    virtual ::CORBA::Long getLocalCCId();
    virtual ::CORBA::Long getNodeId();
    virtual lmp_ipcc_common::IPCC_State getState();
    virtual ::CORBA::Long getRemoteAddress();
    virtual ::CORBA::Short getRemotePortNumber();
    virtual void destroy();
    virtual void enable();
    virtual void disable();
    virtual void registerObserver(
      ::lmp_ipcc_observer::IPCCObserver_ptr  observer);
    virtual void deregisterObserver(
      ::lmp_ipcc_observer::IPCCObserver_ptr  observer);
  private:
    typedef  std::set<::lmp_ipcc_observer::IPCCObserver_var>   IPCCObserverContainer;
    PortableServer::POA_ptr              thePOA;
    lmp_node::NodeApplProxy&             m_node;
    lmp_netif::NetworkIFProxy&           m_networkIf;
    lmp::cc::IpccApplicationIF&          m_ipcc;
    IPCCObserverContainer                m_ipccObservers;
    IpccObserverProxy                    m_ipccObserverProxy;
    lmp_netif::IPCCInDestructionFtorIF&  m_ipccInDestructionFtor;
  };

} // end namespace LMP
