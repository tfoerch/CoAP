# CMakeLists files in this project can
# refer to the root source directory of the project as ${LMP_SOURCE_DIR} and
# to the root binary directory of the project as ${LMP_BINARY_DIR}.
cmake_minimum_required (VERSION 3.3)
project (lmp)
# list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")
option(USE_CLANG "build application with clang" OFF) # OFF is the default
option(USE_SPIRIT_X3 "use spirit X3 for parsing" OFF) # OFF is the default
set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# build local boost and use it
# ./bootstrap.sh --with-toolset=clang --prefix=/home/tom/3rdParty --exec-prefix=/home/tom/3rdParty/clang
# ./b2 clean
# ./b2 toolset=clang cxxflags="-std=c++14 -stdlib=libc++" linkflags="-stdlib=libc++" --prefix=/home/tom/3rdParty --exec-prefix=/home/tom/3rdParty/clang --libdir=/home/tom/3rdParty/clang/lib   --build-dir=/home/tom/3rdParty/boost/build/clang
# ./b2 install toolset=clang cxxflags="-std=c++14 -stdlib=libc++" linkflags="-stdlib=libc++" --prefix=/home/tom/3rdParty --exec-prefix=/home/tom/3rdParty/clang --libdir=/home/tom/3rdParty/clang/lib   --build-dir=/home/tom/3rdParty/boost/build/clang
# ./bootstrap.sh --with-toolset=gcc --prefix=/home/tom/3rdParty --exec-prefix=/home/tom/3rdParty/g++
# ./b2 clean
# ./b2 toolset=gcc cxxflags="-std=c++14" --prefix=/home/tom/3rdParty --exec-prefix=/home/tom/3rdParty/g++ --libdir=/home/tom/3rdParty/g++/lib   --build-dir=/home/tom/3rdParty/boost/build/g++
set(BOOST_ROOT "${PROJECT_SOURCE_DIR}/../../3rdParty")
set(BOOST_INCLUDEDIR "${BOOST_ROOT}/include")
if(USE_CLANG)
SET (CMAKE_CXX_COMPILER             "/usr/bin/clang++-5.0")
SET (CMAKE_C_COMPILER               "/usr/bin/clang-5.0")
SET(_CMAKE_TOOLCHAIN_PREFIX "llvm-")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v -stdlib=libc++")
#set (CMAKE_CXX_FLAGS "-std=c++14 -stdlib=libc++")
#set (CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++ -I/usr/include/libcxxabi")
#set (CMAKE_EXE_LINKER_FLAGS "-lc++abi -v")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
#set (CMAKE_EXE_LINKER_FLAGS "-lc++ -lc++abi -v" )
set(BOOST_LIBRARYDIR "${BOOST_ROOT}/clang/lib")
else(USE_CLANG)
set(BOOST_LIBRARYDIR "${BOOST_ROOT}/g++/lib")
endif(USE_CLANG)

if(USE_SPIRIT_X3)
  add_definitions(-DUSE_SPIRIT_X3_PARSER)
endif(USE_SPIRIT_X3)

#set(CMAKE_VERBOSE_MAKEFILE on)

include( CTest )

find_program(iwyu_path NAMES include-what-you-use iwyu)
if(NOT iwyu_path)
  message(FATAL_ERROR "Could not find the program include-what-you-use")
endif()
option(USE_IWYU "build application with iwyu analysis" OFF) # OFF is the default

# for cppcheck analysis:
#   cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON <path-to-source-directory>
#   cppcheck --project=compile_commands.json --enable=all

find_program( MEMORYCHECK_COMMAND valgrind )
set( MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full" )

set (BUILD_TESTING ON)
set (Boost_TEST_FLAGS "--catch_system_error=yes --log_level=test_suite")
# include(BoostTestTargets)
# include(CppcheckTargets)

include_directories ("${BOOST_INCLUDEDIR}"
                     "${PROJECT_SOURCE_DIR}"
                     "${PROJECT_BINARY_DIR}/idl")

add_subdirectory (base)
add_subdirectory (obj)
add_subdirectory (msg)
add_subdirectory (cc)
add_subdirectory (neighbor)
add_subdirectory (node)
add_subdirectory (idl)
add_subdirectory (server)
add_subdirectory (client)

enable_testing()

SET(MAJOR_VERSION "0")
SET(MINOR_VERSION "2")
SET(PATCH_VERSION "0")
 
SET(CPACK_GENERATOR "DEB")
SET(CPACK_PACKAGE_VERSION_MAJOR "${MAJOR_VERSION}")
SET(CPACK_PACKAGE_VERSION_MINOR "${MINOR_VERSION}")
SET(CPACK_PACKAGE_VERSION_PATCH "${PATCH_VERSION}")
SET(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}_${MAJOR_VERSION}.${MINOR_VERSION}.${CPACK_PACKAGE_VERSION_PATCH}")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}_${MAJOR_VERSION}.${MINOR_VERSION}.${CPACK_PACKAGE_VERSION_PATCH}")
#set(CPACK_DEBIAN_PACKAGE_DEPENDS "cssrobopec,libqt4-xml,libqt4-network,libqtgui4,treeupdatablereeti")
#set(CPACK_PACKAGE_DESCRIPTION "Configure UExhibitor and launch missions")
#set(CPACK_PACKAGE_CONTACT "Adrien BARRAL aba@robopec.com")
#set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_CURRENT_SOURCE_DIR}/Debian/postinst")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Thomas Förch") #required
 
INCLUDE(CPack)
 
# To use this:
# make package
# sudo dpkg -i DistanceBetweenPoints-0.1.1-Linux.deb
