/*
 * UnknownMessageGenerator.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "UnknownMessageGenerator_def.hpp"
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>
#include <iostream>

typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
template struct lmp::msg::generator::unknown_message_grammar<BufOutIterType>;

//namespace lmp
//{
//  namespace msg
//  {
//    lmp::DWORD getLength(
//      const ast::UnknownMessage&  unknownMessage)
//    {
//      lmp::DWORD length =
//        ( lmp::msg::c_headerLength +
//          lmp::obj::getLength(unknownMessage.m_objects) );
//      return length;
//    }
//    bool operator==(
//      const UnknownMessage&  first,
//      const UnknownMessage&  second)
//    {
//      return
//        ( first.m_header == second.m_header &&
//          first.m_objects == second.m_objects );
//    }
//    std::ostream& operator<<(
//      std::ostream&          os,
//      const UnknownMessage&  unknownMessage)
//    {
//      std::cout << "UnknownMessage(" << unknownMessage.m_header
//                << ", " << unknownMessage.m_objects
//                << ")";
//      return os;
//    }
//  } // namespace msg
//} // namespace lmp
