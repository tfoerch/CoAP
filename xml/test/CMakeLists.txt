# Add executable called "LMP_T" that is built from the source files
include_directories ("${PROJECT_SOURCE_DIR}/xml/test")
#set(BOOST_ROOT "${PROJECT_SOURCE_DIR}/../../3rdParty")
#set(BOOST_INCLUDEDIR "${BOOST_ROOT}/include")
#if(USE_CLANG)
#set(BOOST_LIBRARYDIR "${BOOST_ROOT}/clang/lib")
#else(USE_CLANG)
#set(BOOST_LIBRARYDIR "${BOOST_ROOT}/g++/lib")
#endif(USE_CLANG)

find_package(Boost COMPONENTS unit_test_framework)
find_package(ICU COMPONENTS data i18n io uc tu -le-hb test)
enable_testing()
add_executable (XMLUnitTest_T XMLUnitTest.cpp)

#add_boost_test(BaseUnitTest_T
#               SOURCES BaseUnitTest.cpp
#               LIBRARIES lmp_base ${Boost_LIBRARIES})
#add_test(unitTest LMP_T)
#include(CppcheckTargets)
#add_cppcheck(LMP_T UNUSED_FUNCTIONS STYLE POSSIBLE_ERROR FORCE FAIL_ON_WARNINGS)

#if(USE_IWYU)
#set_property(TARGET LMP_T PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
#endif(USE_IWYU)

# Link the executable to the Hello library. Since the Hello library has
# public include directories we will use those link directories when building

target_link_libraries (XMLUnitTest_T LINK_PUBLIC coap_xml ${Boost_LIBRARIES} ${ICU_LIBRARIES})

add_test(NAME xmlUnitTests COMMAND XMLUnitTest_T)


#INSTALL(TARGETS LMP_T DESTINATION bin)
