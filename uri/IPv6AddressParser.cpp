/*
 * IPv6AddressParser.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "uri/IPv6AddressParser_def.hpp"
#include <string>
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct ipv6_address_grammar<BufIterType>;
template struct ipv6_address_grammar<std::string::const_iterator>;
