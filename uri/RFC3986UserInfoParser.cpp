/*
 * RFC3986UserInfoParser.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "uri/RFC3986UserInfoParser_def.hpp"
#include <string>
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct rfc3986::user_info_grammar<BufIterType>;
template struct rfc3986::user_info_grammar<std::string::const_iterator>;
