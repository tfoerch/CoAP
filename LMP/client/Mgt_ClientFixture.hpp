#ifndef MGT_CLIENT_FIXTURE_HPP_
#define MGT_CLIENT_FIXTURE_HPP_

#include <omniORB4/CORBA.h>
#include <boost/optional/optional.hpp>  // for optional
#include <sys/types.h>

namespace lmp_node_registry
{
  class NodeRegistry_i;
}

class LaunchServer
{
public:
  LaunchServer();
  ~LaunchServer();
private:
  static void launchChildProgram(
    unsigned long       nodeId,
    const std::string&  registryURIString);
  LaunchServer(const LaunchServer&); // disabled
public:
  lmp_node_registry::NodeRegistry_i*  theNodeRegistry;
  boost::optional<CORBA::ORB_var>     theOrb;
  unsigned long                       m_1stNodeId;
  pid_t                               m_1stChildPid;
  unsigned long                       m_2ndNodeId;
  pid_t                               m_2ndChildPid;
};
#endif /* MGT_CLIENT_FIXTURE_HPP_ */
