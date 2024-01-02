/*
 * ObjectsParser.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectsParser_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::obj::parser::objects_grammar<BufIterType>;
