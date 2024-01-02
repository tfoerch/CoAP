# Add executable called "LMP_T" that is built from the source files
include_directories ("${PROJECT_SOURCE_DIR}/obj/test")

find_package(Boost COMPONENTS unit_test_framework timer chrono system)

enable_testing()

add_executable (ObjUnitTest_T ObjUnitTest.cpp)

#add_boost_test(ObjUnitTest_T
#               SOURCES ObjUnitTest.cpp
#               LIBRARIES lmp_obj lmp_base ${Boost_LIBRARIES})
#add_test(unitTest LMP_T)
#include(CppcheckTargets)
#add_cppcheck(LMP_T UNUSED_FUNCTIONS STYLE POSSIBLE_ERROR FORCE FAIL_ON_WARNINGS)

#if(USE_IWYU)
#set_property(TARGET LMP_T PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
#endif(USE_IWYU)

# Link the executable to the Hello library. Since the Hello library has
# public include directories we will use those link directories when building

target_link_libraries (ObjUnitTest_T LINK_PUBLIC lmp_obj lmp_base ${Boost_LIBRARIES})

add_test(NAME objUnitTests COMMAND ObjUnitTest_T)



#INSTALL(TARGETS LMP_T DESTINATION bin)
