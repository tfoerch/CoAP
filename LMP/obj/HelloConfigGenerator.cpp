/*
 * HelloConfigGenerator.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/HelloConfigAst.hpp"
#include "obj/HelloConfigGenerator_def.hpp"
#include "obj/ObjectHeaderGenerator_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
template struct lmp::obj::generator::hello_config_grammar<BufOutIterType>;
