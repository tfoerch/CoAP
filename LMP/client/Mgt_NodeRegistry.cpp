#include <Mgt_NodeRegistry.hpp>
#include <iostream>

//static CORBA::Boolean bindObjectToName(CORBA::ORB_ptr, CORBA::Object_ptr);

namespace lmp_node_registry
{

NodeRegistry_i::NodeRegistry_i(
  CORBA::ORB_ptr           orb,
  PortableServer::POA_ptr  poa)
: theORB(CORBA::ORB::_duplicate(orb)),
  thePOA(PortableServer::POA::_duplicate(poa))
{
  //PortableServer::ObjectId *oid=thePOA->activate_object(this); delete oid;
}

NodeRegistry_i::~NodeRegistry_i()
{
  CORBA::release(thePOA);
  CORBA::release(theORB);
}

void NodeRegistry_i::registerNode(
  ::lmp_node::Node_ptr  aNode)
{
  std::cout << "node with node-id = " << aNode->getNodeId() << " registered" << std::endl;
  theNodeByNodeIdMap.insert(NodeByNodeIdMap::value_type(aNode->getNodeId(), ::lmp_node::Node::_duplicate(aNode)));
}

void NodeRegistry_i::deregisterNode(
  ::lmp_node::Node_ptr  aNode)
{
  std::cout << "deregisterNode begin" << std::endl;
  theNodeByNodeIdMap.erase(aNode->getNodeId());
  std::cout << "deregisterNode end" << std::endl;
}

::CORBA::Boolean NodeRegistry_i::isNodeRegistered(
	::CORBA::Long    nodeId)
{
  return
	( theNodeByNodeIdMap.find(nodeId) != theNodeByNodeIdMap.end() );
}

::lmp_node::Node_ptr NodeRegistry_i::getNode(
  ::CORBA::Long    nodeId)
{
  NodeByNodeIdMap::const_iterator nodeIter = theNodeByNodeIdMap.find(nodeId);
  if (nodeIter != theNodeByNodeIdMap.end())
  {
    return nodeIter->second;
  }
  throw lmp_node::No_Such_Entity();
}


void NodeRegistry_i::shutdown()
{
  std::cout << "shutdown begin" << std::endl;
  std::map<CORBA::Long, lmp_node::Node_var>::iterator  iter = theNodeByNodeIdMap.begin();
  while (iter != theNodeByNodeIdMap.end())
  {
	::lmp_node::Node_var  node = iter->second;
	theNodeByNodeIdMap.erase(iter++);
	std::cout << "calling destroy" << std::endl;
	node->destroy();
	std::cout << "return from destroy" << std::endl;
  }
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
//    LMP::NodeRegistry_i* myNodeRegistry = new LMP::NodeRegistry_i(orb, poa);
//
//    PortableServer::ObjectId_var myNodeRegistryId = poa->activate_object(myNodeRegistry);
//
//    // Obtain a reference to the object, and register it in
//    // the naming service.
//    obj = myNodeRegistry->_this();
//
//    CORBA::String_var x;
//    x = orb->object_to_string(obj);
//    std::cout << x << endl;
//
//    if( !bindObjectToName(orb, obj) )
//      return 1;
//
//    myNodeRegistry->_remove_ref();
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
//    // Bind objref with name NodeRegistry to the testContext:
//    CosNaming::Name objectName;
//    objectName.length(1);
//    objectName[0].id   = (const char*) "NodeRegistry";   // string copied
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
