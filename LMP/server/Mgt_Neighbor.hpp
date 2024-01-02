#include <lmp_mgtif_neighbor.hpp>
#include <lmp_mgtif_node.hpp>

#include <omniORB4/CORBA.h>  // for Long
#include <omniORB4/poa.h>                    // for POA_ptr


namespace lmp
{
  namespace neighbor
  {
    class NeighborApplicationIF;
  }
}
namespace lmp_node
{
  class NodeApplProxy;
}

namespace lmp_neighbor
{

class Neighbor_i : public POA_lmp_neighbor::Neighbor
{
public:
  Neighbor_i(
    PortableServer::POA_ptr                poa,
    lmp_node::NodeApplProxy&               node,
    lmp::neighbor::NeighborApplicationIF&  neighbor);
  virtual ~Neighbor_i();
  virtual void destroy();
  virtual void enable();
  virtual void disable();
//  virtual void registerObserver(::LMP::NeighborObserver_ptr observer);
//  virtual void deregisterObserver(::LMP::NeighborObserver_ptr observer);
private:
  PortableServer::POA_ptr                thePOA;
  lmp_node::NodeApplProxy&               m_node;
  lmp::neighbor::NeighborApplicationIF&  m_neighbor;
};

} // end namespace LMP
