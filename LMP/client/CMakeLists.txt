# Add executable called "LMP_T" that is built from the source files

find_package(Boost COMPONENTS chrono system)

include_directories ("${PROJECT_SOURCE_DIR}/client")

add_executable (LMPClient_T Mgt_Client.cpp  Mgt_NodeRegistry.cpp Mgt_IPCCObserver.cpp Mgt_IPCCAdjacencyObserver.cpp Mgt_NeighborAdjacencyObserver.cpp Mgt_ClientFixture.cpp)

#add_cppcheck(LMPClient_T UNUSED_FUNCTIONS STYLE POSSIBLE_ERROR FORCE FAIL_ON_WARNINGS)

if(USE_IWYU)
set_property(TARGET LMPClient_T PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif(USE_IWYU)

# Link the executable to the Hello library. Since the Hello library has
# public include directories we will use those link directories when building
target_link_libraries (LMPClient_T LINK_PUBLIC lmp_mgtif omniORB4 omnithread ${Boost_LIBRARIES} )

INSTALL(TARGETS LMPClient_T DESTINATION bin)
