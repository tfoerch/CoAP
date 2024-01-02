/*
 * UnknownObjectClassGenerator.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/UnknownObjectClassGenerator_def.hpp"
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
template struct lmp::obj::generator::unknown_object_class_grammar<BufOutIterType>;

#if 0
bool lmp::obj::operator==(
  const lmp::obj::UnknownObjectClassData&  first,
  const lmp::obj::UnknownObjectClassData&  second)
{
  return
    ( first.m_object_class == second.m_object_class &&
      first.m_class_type == second.m_class_type &&
      first.m_negotiable == second.m_negotiable &&
      first.m_data == second.m_data );
}

lmp::DWORD lmp::obj::getLength(
  const lmp::obj::UnknownObjectClassData&  unknownObjectClass)
{
  return
    ( c_objHeaderLength +
      unknownObjectClass.m_data.size() );
}

std::ostream& lmp::obj::operator<<(
  std::ostream&                            os,
  const lmp::obj::UnknownObjectClassData&  unknownObjectClass)
{
  using lmp::obj::hex_stream::operator<<;

  os << static_cast<lmp::WORD>(unknownObjectClass.m_object_class) << ", "
     << static_cast<lmp::WORD>(unknownObjectClass.m_class_type) << ", "
     << (unknownObjectClass.m_negotiable ? "negotiable" : "not negotiable") << ", "
     << unknownObjectClass.m_length << ", "
     << unknownObjectClass.m_data;
  return os;
}
#endif
