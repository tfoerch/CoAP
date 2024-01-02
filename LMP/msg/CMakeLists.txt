
add_library (lmp_msg SHARED MessageType.cpp CommonHeaderParser.cpp CommonHeaderGenerator.cpp ConfigParser.cpp ConfigGenerator.cpp ConfigAst.cpp ConfigAckParser.cpp ConfigAckGenerator.cpp ConfigAckAst.cpp ConfigNackParser.cpp ConfigNackGenerator.cpp ConfigNackAst.cpp HelloParser.cpp HelloGenerator.cpp HelloAst.cpp UnknownMessageParser.cpp UnknownMessageGenerator.cpp UnknownMessageAst.cpp MessageParser.cpp MessageGenerator.cpp MessageAst.cpp)

#add_cppcheck(lmp_msg UNUSED_FUNCTIONS STYLE POSSIBLE_ERROR FORCE FAIL_ON_WARNINGS)

if(USE_IWYU)
set_property(TARGET lmp_msg PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif(USE_IWYU)

enable_testing()

add_subdirectory (test)

target_include_directories (lmp_msg PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

INSTALL(TARGETS lmp_msg DESTINATION lib)
