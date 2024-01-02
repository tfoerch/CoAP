#include <Mgt_IPCCObserver.hpp>
#include <lmp_mgtif_ipcc.hpp>

namespace lmp_ipcc_observer
{

IPCCObserver_i::IPCCObserver_i(
  CORBA::ORB_ptr           orb,
  PortableServer::POA_ptr  poa)
: theORB(CORBA::ORB::_duplicate(orb)),
  thePOA(PortableServer::POA::_duplicate(poa))
{
  //PortableServer::ObjectId *oid=thePOA->activate_object(this); delete oid;
}

IPCCObserver_i::~IPCCObserver_i()
{
  CORBA::release(thePOA);
  CORBA::release(theORB);
}

void IPCCObserver_i::destroy()
{
  PortableServer::ObjectId* oid=thePOA->servant_to_id(this);
  std::cout << "before deactivate_object" << std::endl;
  thePOA->deactivate_object(*oid);  delete oid;
  std::cout << "after deactivate_object" << std::endl;
  // _remove_ref(); // delete this;
}

void IPCCObserver_i::eventProcessed(
  ::lmp_ipcc::IPCC_ptr              aIPCC,
  ::lmp_ipcc_observer::IPCC_Event   event,
  ::lmp_ipcc_common::IPCC_State     sourceState,
  ::lmp_ipcc_common::IPCC_State     targetState,
  ::lmp_ipcc_observer::IPCC_Action  action)
{
  ::CORBA::Long    localCCId =  aIPCC->getLocalCCId();
  ::CORBA::Long    nodeId =  aIPCC->getNodeId();
  std::cout << "Node[" << nodeId << "].Ipcc[" << localCCId << "].eventProcessed("
            << event << ", "
            << sourceState << " -> "
            << targetState << ", "
            << action << ")" << std::endl;
}

void IPCCObserver_i::peerIpccDiscovered(
  ::lmp_ipcc::IPCC_ptr              aIPCC,
  ::CORBA::Long                     remoteNodeId,
  ::CORBA::Long                     remoteCCId)
{
  ::CORBA::Long    localCCId =  aIPCC->getLocalCCId();
  ::CORBA::Long    nodeId =  aIPCC->getNodeId();
  std::cout << "Node[" << nodeId << "].Ipcc[" << localCCId << "].peerIpccDiscovered("
            << remoteNodeId << ", "
            << remoteCCId << ")" << std::endl;
}

std::ostream& operator<<(
  std::ostream&                     os,
  ::lmp_ipcc_observer::IPCC_Event   event)
{
  switch(event)
  {
    case ::lmp_ipcc_observer::EvBringUp:
      std::cout << "EvBringUp";
      break;
    case ::lmp_ipcc_observer::EvCCDn:
      std::cout << "EvCCDn";
      break;
    case ::lmp_ipcc_observer::EvConfDone:
      std::cout << "EvConfDone";
      break;
    case ::lmp_ipcc_observer::EvConfErr:
      std::cout << "EvConfErr";
      break;
    case ::lmp_ipcc_observer::EvNewConfOK:
      std::cout << "EvNewConfOK";
      break;
    case ::lmp_ipcc_observer::EvNewConfErr:
      std::cout << "EvNewConfErr";
      break;
    case ::lmp_ipcc_observer::EvContenWin:
      std::cout << "EvContenWin";
      break;
    case ::lmp_ipcc_observer::EvContenLost:
      std::cout << "EvContenLost";
      break;
    case ::lmp_ipcc_observer::EvAdminDown:
      std::cout << "EvAdminDown";
      break;
    case ::lmp_ipcc_observer::EvNbrGoesDn:
      std::cout << "EvNbrGoesDn";
      break;
    case ::lmp_ipcc_observer::EvHelloRcvd:
      std::cout << "EvHelloRcvd";
      break;
    case ::lmp_ipcc_observer::EvHoldTimer:
      std::cout << "EvHoldTimer";
      break;
    case ::lmp_ipcc_observer::EvSeqNumErr:
      std::cout << "EvSeqNumErr";
      break;
    case ::lmp_ipcc_observer::EvReconfig:
      std::cout << "EvReconfig";
      break;
    case ::lmp_ipcc_observer::EvConfRet:
      std::cout << "EvConfRet";
      break;
    case ::lmp_ipcc_observer::EvHelloRet:
      std::cout << "EvHelloRet";
      break;
    case ::lmp_ipcc_observer::EvDownTimer:
      std::cout << "EvDownTimer";
      break;
  }
  return os;
}

std::ostream& operator<<(
  std::ostream&                   os,
  ::lmp_ipcc_common::IPCC_State   state)
{
  switch(state)
  {
    case ::lmp_ipcc_common::IPCC_Down:
      std::cout << "Down";
      break;
    case ::lmp_ipcc_common::IPCC_ConfSend:
      std::cout << "ConfSend";
      break;
    case ::lmp_ipcc_common::IPCC_ConfRecv:
      std::cout << "onfRecv";
      break;
    case ::lmp_ipcc_common::IPCC_Active:
      std::cout << "Active";
      break;
    case ::lmp_ipcc_common::IPCC_Up:
      std::cout << "Up";
      break;
    case ::lmp_ipcc_common::IPCC_GoingDown:
      std::cout << "GoingDown";
      break;
  }
  return os;
}

std::ostream& operator<<(
  std::ostream&                     os,
  ::lmp_ipcc_observer::IPCC_Action  action)
{
  switch(action)
  {
    case ::lmp_ipcc_observer::ActionSendConfig:
      std::cout << "ActionSendConfig";
      break;
    case ::lmp_ipcc_observer::ActionStopSendConfig:
      std::cout << "ActionStopSendConfig";
      break;
    case ::lmp_ipcc_observer::ActionResendConfig:
      std::cout << "ActionResendConfig";
      break;
    case ::lmp_ipcc_observer::ActionSendConfigAck:
      std::cout << "ActionSendConfigAck";
      break;
    case ::lmp_ipcc_observer::ActionSendConfigNack:
      std::cout << "ActionSendConfigNack";
      break;
    case ::lmp_ipcc_observer::ActionSendHello:
      std::cout << "ActionSendHello";
      break;
    case ::lmp_ipcc_observer::ActionStopSendHello:
      std::cout << "ActionStopSendHello";
      break;
    case ::lmp_ipcc_observer::ActionSetCCDownFlag:
      std::cout << "ActionSetCCDownFlag";
      break;
    case ::lmp_ipcc_observer::ActionClearCCDownFlag:
      std::cout << "ActionClearCCDownFlag";
      break;
    case ::lmp_ipcc_observer::ActionNoAction:
      std::cout << "ActionNoAction";
      break;
  }
  return os;
}

} // end namespace LMP

//int
//main(int argc, char **argv)
//{
//  try {
//    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);
//
//    CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
//    PortableServer::POA_var poa = PortableServer::POA::_narrow(obj);
//
//    LMP::IPCCObserver_i* myIPCCObserver = new LMP::IPCCObserver_i(orb, poa);
//
//    PortableServer::ObjectId_var myIPCCObserverId = poa->activate_object(myIPCCObserver);
//
//    // Obtain a reference to the object, and register it in
//    // the naming service.
//    obj = myIPCCObserver->_this();
//
//    CORBA::String_var x;
//    x = orb->object_to_string(obj);
//    std::cout << x << endl;
//
//    if( !bindObjectToName(orb, obj) )
//      return 1;
//
//    myIPCCObserver->_remove_ref();
//
//    PortableServer::POAManager_var pman = poa->the_POAManager();
//    pman->activate();
//
//    orb->run();
//  }
//  catch(CORBA::SystemException& ex) {
//    cerr << "Caught CORBA::" << ex._name() << endl;
//  }
//  catch(CORBA::Exception& ex) {
//    cerr << "Caught CORBA::Exception: " << ex._name() << endl;
//  }
//  catch(omniORB::fatalException& fe) {
//    cerr << "Caught omniORB::fatalException:" << endl;
//    cerr << "  file: " << fe.file() << endl;
//    cerr << "  line: " << fe.line() << endl;
//    cerr << "  mesg: " << fe.errmsg() << endl;
//  }
//  return 0;
//}

//////////////////////////////////////////////////////////////////////

//static CORBA::Boolean
//bindObjectToName(CORBA::ORB_ptr orb, CORBA::Object_ptr objref)
//{
//  CosNaming::NamingContext_var rootContext;
//
//  try {
//    // Obtain a reference to the root context of the Name service:
//    CORBA::Object_var obj;
//    obj = orb->resolve_initial_references("NameService");
//
//    // Narrow the reference returned.
//    rootContext = CosNaming::NamingContext::_narrow(obj);
//    if( CORBA::is_nil(rootContext) ) {
//      cerr << "Failed to narrow the root naming context." << endl;
//      return 0;
//    }
//  }
//  catch (CORBA::NO_RESOURCES&) {
//    cerr << "Caught NO_RESOURCES exception. You must configure omniORB "
//	 << "with the location" << endl
//	 << "of the naming service." << endl;
//    return 0;
//  }
//  catch (CORBA::ORB::InvalidName&) {
//    // This should not happen!
//    cerr << "Service required is invalid [does not exist]." << endl;
//    return 0;
//  }
//
//  try {
//    // Bind a context called "test" to the root context:
//
//    CosNaming::Name contextName;
//    contextName.length(1);
//    contextName[0].id   = (const char*) "test";       // string copied
//    contextName[0].kind = (const char*) "my_context"; // string copied
//    // Note on kind: The kind field is used to indicate the type
//    // of the object. This is to avoid conventions such as that used
//    // by files (name.type -- e.g. test.ps = postscript etc.)
//
//    CosNaming::NamingContext_var testContext;
//    try {
//      // Bind the context to root.
//      testContext = rootContext->bind_new_context(contextName);
//    }
//    catch(CosNaming::NamingContext::AlreadyBound& ex) {
//      // If the context already exists, this exception will be raised.
//      // In this case, just resolve the name and assign testContext
//      // to the object returned:
//      CORBA::Object_var obj;
//      obj = rootContext->resolve(contextName);
//      testContext = CosNaming::NamingContext::_narrow(obj);
//      if( CORBA::is_nil(testContext) ) {
//        cerr << "Failed to narrow naming context." << endl;
//        return 0;
//      }
//    }
//
//    // Bind objref with name IPCCObserver to the testContext:
//    CosNaming::Name objectName;
//    objectName.length(1);
//    objectName[0].id   = (const char*) "IPCCObserver";   // string copied
//    objectName[0].kind = (const char*) "Object"; // string copied
//
//    try {
//      testContext->bind(objectName, objref);
//    }
//    catch(CosNaming::NamingContext::AlreadyBound& ex) {
//      testContext->rebind(objectName, objref);
//    }
//    // Note: Using rebind() will overwrite any Object previously bound
//    //       to /test/Node with obj.
//    //       Alternatively, bind() can be used, which will raise a
//    //       CosNaming::NamingContext::AlreadyBound exception if the name
//    //       supplied is already bound to an object.
//
//    // Amendment: When using OrbixNames, it is necessary to first try bind
//    // and then rebind, as rebind on it's own will throw a NotFoundexception if
//    // the Name has not already been bound. [This is incorrect behaviour -
//    // it should just bind].
//  }
//  catch(CORBA::TRANSIENT& ex) {
//    cerr << "Caught system exception TRANSIENT -- unable to contact the "
//         << "naming service." << endl
//	 << "Make sure the naming server is running and that omniORB is "
//	 << "configured correctly." << endl;
//
//    return 0;
//  }
//  catch(CORBA::SystemException& ex) {
//    cerr << "Caught a CORBA::" << ex._name()
//	 << " while using the naming service." << endl;
//    return 0;
//  }
//  return 1;
//}
