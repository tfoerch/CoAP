/*
 * UnknownCCIdCType.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/UnknownCCIdCTypeAst.hpp"
#include "obj/ObjectClassUnknownCTypeGenerator_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
template struct lmp::obj::generator::object_class_unknown_ctype_grammar<BufOutIterType, lmp::obj::ObjectClass::ControlChannelID>;
#if 0
template std::ostream& lmp::obj::operator<< <lmp::obj::ObjectClassTraits<lmp::obj::ObjectClass::ControlChannelID>>(
  std::ostream&,
  const lmp::obj::ObjectClassUnknownCTypeData<lmp::obj::ObjectClassTraits<lmp::obj::ObjectClass::ControlChannelID>>&);
template bool lmp::obj::operator== <lmp::obj::ObjectClassTraits<lmp::obj::ObjectClass::ControlChannelID>>(
  const lmp::obj::ObjectClassUnknownCTypeData<lmp::obj::ObjectClassTraits<lmp::obj::ObjectClass::ControlChannelID>>&,
  const lmp::obj::ObjectClassUnknownCTypeData<lmp::obj::ObjectClassTraits<lmp::obj::ObjectClass::ControlChannelID>>&);
#endif
