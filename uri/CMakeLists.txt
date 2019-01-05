
add_library (coap_uri SHARED RFC3986IPv4AddressParser.cpp RFC3986IPv6AddressParser.cpp RFC3986IPvFutureParser.cpp RFC3986IPLiteralParser.cpp RFC3986UnreservedParser.cpp RFC3986SubDelimsParser.cpp RFC3986GenDelimsParser.cpp RFC3986PercentEncodedParser.cpp RFC3986RegNameParser.cpp RFC3986HostParser.cpp RFC3986UserInfoParser.cpp RFC3986PortParser.cpp RFC3986AuthorityParser.cpp RFC3986PCharParser.cpp RFC3986SegmentParser.cpp RFC3986PathAbEmptyParser.cpp RFC3986SegmentNZParser.cpp RFC3986PathAbsoluteParser.cpp RFC3986PathRootLessParser.cpp RFC3986PathEmptyParser.cpp RFC3986HierPartParser.cpp RFC3986QueryAndFragmentParser.cpp RFC3986SchemeParser.cpp RFC3986UriParser.cpp)

#add_cppcheck(lmp_base UNUSED_FUNCTIONS STYLE POSSIBLE_ERROR FORCE FAIL_ON_WARNINGS)
# cppcheck_sources (lmp_cc SOURCES IPCC_FSM.cpp IPCC_Impl.cpp INCLUDES IPCC_FSM.hpp IPCC_Impl.hpp IPCC_FSM_InvokeIF.hpp IPCC_Msg_ReceiveIF.hpp IPCC_ObserverIF.hpp)

if(USE_IWYU)
set_property(TARGET coap_uri PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif(USE_IWYU)

enable_testing()

add_subdirectory (test)

target_include_directories (coap_uri PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

INSTALL(TARGETS coap_uri DESTINATION lib)
