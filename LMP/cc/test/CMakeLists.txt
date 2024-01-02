# Add executable called "LMP_T" that is built from the source files
include_directories ("${PROJECT_SOURCE_DIR}/cc/test")

find_package ( Threads REQUIRED )
find_package( Boost REQUIRED COMPONENTS unit_test_framework program_options system timer chrono thread )

enable_testing()

add_executable (CCUnitTest_T CCUnitTest.cpp Test_Wait.cpp Test_IPCC_Observer.cpp Test_IPCC_Msg_Receiver.cpp Test_NeighborDiscoveredCheckFtor.cpp Test_EventCallbackCalledCheckFtor.cpp Test_NoTimeoutScheduledCheckFtor.cpp)

# add_boost_test(CCUnitTest_T
# SOURCES CCUnitTest.cpp Test_Wait.cpp Test_IPCC_Observer.cpp Test_IPCC_Msg_Receiver.cpp Test_NeighborDiscoveredCheckFtor.cpp Test_EventCallbackCalledCheckFtor.cpp Test_NoTimeoutScheduledCheckFtor.cpp
# LIBRARIES lmp_cc lmp_msg lmp_obj lmp_base lmp_node lmp_neighbor ${Boost_LIBRARIES} )
#add_test(unitTest LMP_T)
#include(CppcheckTargets)
#add_cppcheck(LMP_T UNUSED_FUNCTIONS STYLE POSSIBLE_ERROR FORCE FAIL_ON_WARNINGS)

#if(USE_IWYU)
#set_property(TARGET LMP_T PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
#endif(USE_IWYU)

# Link the executable to the Hello library. Since the Hello library has
# public include directories we will use those link directories when building
target_link_libraries (CCUnitTest_T LINK_PUBLIC lmp_cc lmp_msg lmp_obj lmp_base lmp_node lmp_neighbor ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} )

#add_test(NAME ccUnitTests COMMAND CCUnitTest_T)
add_test(NAME retrTimerLimitSTUnitTest COMMAND CCUnitTest_T --run_test=lmp_socket/retransmitTimer_retryLimit_singleThread)
add_test(NAME retrTimerLimitUnitTest COMMAND CCUnitTest_T --run_test=lmp_socket/retransmitTimer_retryLimit)
add_test(NAME retrTimerStopUnitTest COMMAND CCUnitTest_T --run_test=lmp_socket/retransmitTimer_stop)
add_test(NAME getIfAddressUnitTest COMMAND CCUnitTest_T --run_test=lmp_socket/getIfAddress)
add_test(NAME bind2LoopbackAddrUnitTest COMMAND CCUnitTest_T --run_test=lmp_socket/bind_socket_to_loopback_addr)
add_test(NAME bind2NetworkIfUnitTest COMMAND CCUnitTest_T --run_test=lmp_socket/bind_socket_to_netif)
add_test(NAME evCCDownUnitTest COMMAND CCUnitTest_T --run_test=lmp_ipcc_active/activeIPCC_CCDown)
add_test(NAME evAdmimDownUnitTest COMMAND CCUnitTest_T --run_test=lmp_ipcc_active/activeIPCC_AdminDown)
add_test(NAME evConfigErrUnitTest COMMAND CCUnitTest_T --run_test=lmp_ipcc_active/activeIPCC_ConfigErr)
add_test(NAME evContenWinUnitTest COMMAND CCUnitTest_T --run_test=lmp_ipcc_active/activeIPCC_ContenWin)
add_test(NAME evReconfigUnitTest COMMAND CCUnitTest_T --run_test=lmp_ipcc_active/activeIPCC_Reconfig)
add_test(NAME evConfRetUnitTest COMMAND CCUnitTest_T --run_test=lmp_ipcc_active/activeIPCC_ConfRet)
add_test(NAME evContLostNotAcceptConfUnitTest COMMAND CCUnitTest_T --run_test=lmp_ipcc_active/activeIPCC_ContenLost_NotAcceptConf)
add_test(NAME evHelloRcvdUnitTest COMMAND CCUnitTest_T --run_test=lmp_ipcc_active/activeIPCC_ConfDone_HelloRcvd)
add_test(NAME evContLostAcceptConfUnitTest COMMAND CCUnitTest_T --run_test=lmp_ipcc_active/activeIPCC_ContenLost_AcceptConf)
add_test(NAME passiveUnitTest COMMAND CCUnitTest_T --run_test=lmp_ipcc_passive/passiveIPCC)


#INSTALL(TARGETS LMP_T DESTINATION bin)
