/*
 * RFC3986IPv6AddressGenerator.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "RFC3986IPv6AddressGenerator_def.hpp"
#include <string>
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
template struct rfc3986::generator::ipv6_address_grammar<BufOutIterType>;
typedef std::back_insert_iterator<std::string>  StrOutIterType;
template struct rfc3986::generator::ipv6_address_grammar<StrOutIterType>;
