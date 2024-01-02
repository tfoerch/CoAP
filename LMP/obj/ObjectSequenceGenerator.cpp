/*
 * ObjectSequenceGenerator.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectSequenceGenerator_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
template struct lmp::obj::generator::object_sequence_grammar<BufOutIterType>;

//lmp::DWORD lmp::obj::getLength(
//  const lmp::obj::ObjectSequence&  objectSequence)
//{
//  lmp::DWORD length = 0;
//  for (std::vector<lmp::obj::Objects>::const_iterator iter = objectSequence.begin();
//       iter != objectSequence.end();
//       ++iter)
//  {
//    length += lmp::obj::getLength(*iter);
//  }
//  return length;
//}
//
//std::ostream& lmp::obj::operator<<(
//  std::ostream&             os,
//  const lmp::obj::ObjectSequence&  objectSequence)
//{
//  for (std::vector<lmp::obj::Objects>::const_iterator iter = objectSequence.begin();
//       iter != objectSequence.end();
//       ++iter)
//  {
//    if (iter != objectSequence.begin())
//    {
//      os << ", ";
//    }
//    os << *iter;
//  }
//  return os;
//}
