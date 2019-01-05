/*
 * RFC3986PathAbEmptyParser.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "uri/RFC3986PathAbEmptyParser_def.hpp"
#include <string>
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct rfc3986::path_ab_empty_grammar<BufIterType>;
template struct rfc3986::path_ab_empty_grammar<std::string::const_iterator>;
