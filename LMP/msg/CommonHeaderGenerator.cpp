/*
 * CommonHeaderGenerator.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "CommonHeaderGenerator_def.hpp"
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
template struct lmp::msg::generator::common_header_unknown_msgType_grammar<BufOutIterType>;
