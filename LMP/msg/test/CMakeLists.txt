# Add executable called "LMP_T" that is built from the source files
include_directories ("${PROJECT_SOURCE_DIR}/msg/test")

find_package(Boost COMPONENTS unit_test_framework timer chrono system)

enable_testing()

add_executable (MsgUnitTest_T MsgUnitTest.cpp)

#add_boost_test(MsgUnitTest_T
#               SOURCES MsgUnitTest.cpp
#               LIBRARIES lmp_msg lmp_obj lmp_base ${Boost_LIBRARIES})
#add_test(unitTest LMP_T)
#include(CppcheckTargets)
#add_cppcheck(LMP_T UNUSED_FUNCTIONS STYLE POSSIBLE_ERROR FORCE FAIL_ON_WARNINGS)

#if(USE_IWYU)
#set_property(TARGET LMP_T PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
#endif(USE_IWYU)

# Link the executable to the Hello library. Since the Hello library has
# public include directories we will use those link directories when building

target_link_libraries (MsgUnitTest_T LINK_PUBLIC lmp_msg lmp_obj lmp_base ${Boost_LIBRARIES})

add_test(NAME configMsgUnitTests COMMAND MsgUnitTest_T --run_test=msg/config_message_spirit)
add_test(NAME configAckMsgUnitTests COMMAND MsgUnitTest_T --run_test=msg/config_ack_message_spirit)
add_test(NAME configNackMsgUnitTests COMMAND MsgUnitTest_T --run_test=msg/config_nack_message_spirit)
add_test(NAME helloMsgUnitTests COMMAND MsgUnitTest_T --run_test=msg/hello_message_spirit)
add_test(NAME unknownMsgUnitTests COMMAND MsgUnitTest_T --run_test=msg/unknown_message_spirit)
add_test(NAME unknownMsgTypeHeaderUnitTests COMMAND MsgUnitTest_T --run_test=msg/unknown_msg_type_header_spirit)
#add_test(NAME msgUnitTests COMMAND MsgUnitTest_T)


#INSTALL(TARGETS LMP_T DESTINATION bin)
