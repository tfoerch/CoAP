/*
 * CommonHeaderParser.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "CommonHeaderParser_def.hpp"
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::msg::parser::common_header_flags_grammar<BufIterType>;
template struct lmp::msg::parser::common_header_length_grammar<BufIterType>;

