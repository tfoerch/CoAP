
add_library (lmp_obj SHARED UnknownObjectClassParser.cpp  UnknownObjectClassGenerator.cpp ObjectHeaderUnknownObjectClassGenerator.cpp LocalCCIdGenerator.cpp LocalCCIdParser.cpp LocalCCIdAst.cpp RemoteCCIdGenerator.cpp RemoteCCIdParser.cpp RemoteCCIdAst.cpp UnknownCCIdCTypeParser.cpp UnknownCCIdCTypeGenerator.cpp LocalNodeIdGenerator.cpp LocalNodeIdParser.cpp LocalNodeIdAst.cpp RemoteNodeIdGenerator.cpp RemoteNodeIdParser.cpp RemoteNodeIdAst.cpp UnknownNodeIdCTypeGenerator.cpp UnknownNodeIdCTypeParser.cpp MessageIdGenerator.cpp MessageIdParser.cpp MessageIdAst.cpp MessageIdAckGenerator.cpp MessageIdAckParser.cpp MessageIdAckAst.cpp UnknownMessageIdCTypeGenerator.cpp UnknownMessageIdCTypeParser.cpp HelloConfigGenerator.cpp HelloConfigParser.cpp HelloConfigAst.cpp UnknownConfigCTypeGenerator.cpp UnknownConfigCTypeParser.cpp HelloGenerator.cpp HelloParser.cpp HelloAst.cpp UnknownHelloCTypeGenerator.cpp UnknownHelloCTypeParser.cpp ControlChannelIdCTypesGenerator.cpp ControlChannelIdCTypesParser.cpp ControlChannelIdCTypesAst.cpp NodeIdCTypesParser.cpp NodeIdCTypesGenerator.cpp NodeIdCTypesAst.cpp MessageIdCTypesParser.cpp MessageIdCTypesGenerator.cpp MessageIdCTypesAst.cpp ConfigCTypesGenerator.cpp ConfigCTypesParser.cpp ConfigCTypesAst.cpp HelloCTypesParser.cpp HelloCTypesGenerator.cpp HelloCTypesAst.cpp ConfigObjectSequenceParser.cpp ConfigObjectSequenceGenerator.cpp ObjectsParser.cpp ObjectsGenerator.cpp ObjectsAst.cpp ObjectSequenceParser.cpp ObjectSequenceGenerator.cpp ObjectSequenceAst.cpp ) 

# add_library (lmp_obj SHARED ObjectClass.cpp UnknownObjectClass.cpp ByteSequence.cpp
# ControlChannelIdClass.cpp LocalCCId.cpp RemoteCCId.cpp UnknownCCIdCType.cpp ControlChannelIdCTypes.cpp NodeIdClass.cpp LocalNodeId.cpp RemoteNodeId.cpp UnknownNodeIdCType.cpp NodeIdCTypes.cpp # MessageIdClass.cpp MessageId.cpp MessageIdAck.cpp UnknownMessageIdCType.cpp MessageIdCTypes.cpp ConfigClass.cpp HelloConfig.cpp UnknownConfigCType.cpp ConfigCTypes.cpp HelloClass.cpp Hello.cpp UnknownHelloCType.cpp HelloCTypes.cpp Objects.cpp ConfigObjectSequence.cpp ObjectSequence.cpp LocalCCIdParser.cpp) 

#add_cppcheck(lmp_obj UNUSED_FUNCTIONS STYLE POSSIBLE_ERROR FORCE FAIL_ON_WARNINGS)

if(USE_IWYU)
set_property(TARGET lmp_obj PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif(USE_IWYU)

enable_testing()

add_subdirectory (test)

target_include_directories (lmp_obj PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

INSTALL(TARGETS lmp_obj DESTINATION lib)
