
#include <Mgt_ClientFixture.hpp>
#include <Mgt_NodeRegistry.hpp>
#include <omniORB4/CORBA.h>
#include <omniORB4/poa.h>                         // for POA_var, POA, etc
#include <omniORB4/templatedecls.h>
#include <omniORB4/templatedefns.h>
#include <omniORB4/userexception.h>               // for TRANSIENT

#include <boost/test/unit_test_suite.hpp>
// #include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <chrono>
#include <unistd.h>                               // for execve, fork
#include <sys/wait.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include <net/if.h>
// #include <ifaddrs.h>
// #include <errno.h>

LaunchServer::LaunchServer()
  : theNodeRegistry(0),
    theOrb(),
    m_1stNodeId(10001),
    m_1stChildPid(0),
    m_2ndNodeId(10002),
    m_2ndChildPid(0)
{
  std::cout << "launch server setup\n";
  try
  {
    theOrb =
      CORBA::ORB_init(boost::unit_test::framework::master_test_suite().argc,
                      boost::unit_test::framework::master_test_suite().argv);
    if (theOrb)
    {
      CORBA::ORB_var orb = *theOrb;
      CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
      PortableServer::POA_var poa = PortableServer::POA::_narrow(obj);

      theNodeRegistry = new lmp_node_registry::NodeRegistry_i(orb, poa);

      PortableServer::ObjectId_var myNodeRegistryId = poa->activate_object(theNodeRegistry);

      // Obtain a reference to the object, and register it in
      // the naming service.
      obj = theNodeRegistry->_this();

      CORBA::String_var x = orb->object_to_string(obj);
      std::ostringstream registryURIStream;
      //std::cout << x << std::endl;
      registryURIStream << x << std::ends;
      std::string  registryURIString(registryURIStream.str());

      PortableServer::POAManager_var pman = poa->the_POAManager();
      pman->activate();

      if (orb->work_pending())
      {
        orb->perform_work();
      };

      m_1stChildPid = fork();

      if (m_1stChildPid == -1)
      {
        // error, failed to fork()
      }
      else if (m_1stChildPid > 0)
      {
        m_2ndChildPid = fork();

        if (m_2ndChildPid == -1)
        {
          // error, failed to fork()
        }
        else if (m_2ndChildPid > 0)
        {
          std::chrono::system_clock::time_point expireTime =
            std::chrono::system_clock::now() + std::chrono::milliseconds(500);
          {
            std::chrono::system_clock::time_point  now  = std::chrono::system_clock::now();
            std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
            std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds>(ms);
            std::time_t now_c = s.count();
            std::size_t fractional_seconds = ms.count() % 1000;
            std::cout << std::put_time(std::localtime(&now_c), "%T.") << fractional_seconds << ": enter while" << std::endl;
          }
          while (std::chrono::system_clock::now() < expireTime)
          {
            // std::cout << std::chrono::system_clock::now() << ": checking work_pending()" << std::endl;
            if (orb->work_pending())
            {
              {
                std::chrono::system_clock::time_point  now  = std::chrono::system_clock::now();
                std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
                std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds>(ms);
                std::time_t now_c = s.count();
                std::size_t fractional_seconds = ms.count() % 1000;
                std::cout << std::put_time(std::localtime(&now_c), "%T.") << fractional_seconds << ": enter perform_work()" << std::endl;
              }
              orb->perform_work();
              {
                std::chrono::system_clock::time_point  now  = std::chrono::system_clock::now();
                std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
                std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds>(ms);
                std::time_t now_c = s.count();
                std::size_t fractional_seconds = ms.count() % 1000;
                std::cout << std::put_time(std::localtime(&now_c), "%T.") << fractional_seconds << ": leaving perform_work()" << std::endl;
              }
            }
          }
          {
            std::chrono::system_clock::time_point  now  = std::chrono::system_clock::now();
            std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
            std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds>(ms);
            std::time_t now_c = s.count();
            std::size_t fractional_seconds = ms.count() % 1000;
            std::cout << std::put_time(std::localtime(&now_c), "%T.") << fractional_seconds << ": leaving while" << std::endl;
          }
          //theNodeRegistry->isNodeRegistered(m_1stNodeId;);
        }
        else
        { // we are the 2nd child
          launchChildProgram(m_2ndNodeId, registryURIString);
        }
      }
      else
      { // we are the 1st child
        launchChildProgram(m_1stNodeId, registryURIString);
      }

      // orb->run();
    }
  }
  catch(CORBA::TRANSIENT&)
  {
    std::cerr << "Caught system exception TRANSIENT -- unable to contact the "
         << "server." << std::endl;
  }
  catch(CORBA::SystemException& ex)
  {
    std::cerr << "Caught a CORBA::" << ex._name() << std::endl;
  }
  catch(CORBA::Exception& ex)
  {
    std::cerr << "Caught CORBA::Exception: " << ex._name() << std::endl;
  }
  catch(omniORB::fatalException& fe)
  {
    std::cerr << "Caught omniORB::fatalException:" << std::endl;
    std::cerr << "  file: " << fe.file() << std::endl;
    std::cerr << "  line: " << fe.line() << std::endl;
    std::cerr << "  mesg: " << fe.errmsg() << std::endl;
  }
}

LaunchServer::~LaunchServer()
{
  std::cout << "launch server teardown\n";
  if (theNodeRegistry)
  {
    std::cout << "calling shutdown" << std::endl;
    theNodeRegistry->shutdown();
  }
  int status;
  waitpid(m_1stChildPid, &status, 0);
}

void LaunchServer::launchChildProgram(
  unsigned long       nodeId,
  const std::string&  registryURIString)
{
  const char serverPath[] = "/home/tom/build/LMP/g++/server/LMPServer_T";
  const char nodeIdOptStr[] = "--node-id";
  const char nodeRegistryOptStr[] = "--node-registry";
  std::ostringstream nodeIdStream;
  nodeIdStream << nodeId << std::ends;
  const char* newargv[] =
  { serverPath,
    serverPath,
    nodeIdOptStr,
    nodeIdStream.str().c_str(),
    nodeRegistryOptStr,
    registryURIString.c_str(),
    nullptr
  };
  std::cout << newargv[0] << " "
     << newargv[1] << " "
     << newargv[2] << " "
     << newargv[3] << " "
     << newargv[4] << " "
     << newargv[5] << std::endl;
  char* newenviron[] = { NULL };
  execve(newargv[0], const_cast<char* const*>(newargv), newenviron);
  perror("execve");   /* execve() only returns on error */
  exit(EXIT_FAILURE);   // exec never returns

}

