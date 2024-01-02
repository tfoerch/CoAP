# Add executable called "LMP_T" that is built from the source files
include_directories ("${PROJECT_SOURCE_DIR}/node/test")

find_package(Boost COMPONENTS unit_test_framework timer chrono system)
#add_executable (LMP_T Test_IPCC_Observer.cpp TestMain.cpp)
enable_testing()
add_executable (NodeUnitTest_T NodeUnitTest.cpp)

#add_boost_test(NodeUnitTest_T
#               SOURCES NodeUnitTest.cpp
#               LIBRARIES lmp_node lmp_neighbor ${Boost_LIBRARIES})
#add_test(unitTest LMP_T)
#include(CppcheckTargets)
#add_cppcheck(LMP_T UNUSED_FUNCTIONS STYLE POSSIBLE_ERROR FORCE FAIL_ON_WARNINGS)

#if(USE_IWYU)
#set_property(TARGET LMP_T PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
#endif(USE_IWYU)

# Link the executable to the Hello library. Since the Hello library has
# public include directories we will use those link directories when building

target_link_libraries (NodeUnitTest_T LINK_PUBLIC lmp_base lmp_node lmp_neighbor ${Boost_LIBRARIES})

add_test(NAME nodeUnitTests COMMAND NodeUnitTest_T)


#INSTALL(TARGETS LMP_T DESTINATION bin)
