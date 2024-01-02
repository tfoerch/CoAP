
add_library (lmp_cc SHARED IPCC_FSM.cpp IPCC_Impl.cpp IPCC_NetIFSocket.cpp UDP_Msg_Handler.cpp IPCC_State.cpp IPCC_Event.cpp IPCC_Action.cpp)

#add_cppcheck(lmp_cc UNUSED_FUNCTIONS STYLE POSSIBLE_ERROR FORCE FAIL_ON_WARNINGS)
# cppcheck_sources (lmp_cc SOURCES IPCC_FSM.cpp IPCC_Impl.cpp INCLUDES IPCC_FSM.hpp IPCC_Impl.hpp IPCC_FSM_InvokeIF.hpp IPCC_Msg_ReceiveIF.hpp IPCC_ObserverIF.hpp)

if(USE_IWYU)
  set_property(TARGET lmp_cc PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif(USE_IWYU)

enable_testing()

add_subdirectory (test)

target_include_directories (lmp_cc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

INSTALL(TARGETS lmp_cc DESTINATION lib)
