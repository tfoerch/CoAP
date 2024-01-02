/*
 * UnknownMessageAst.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "UnknownMessageAst.hpp"

namespace lmp
{
  namespace msg
  {
    namespace ast
    {
      lmp::WORD getLength(
        const UnknownMessage&  unknownMessage)
      {
        lmp::DWORD length =
          ( lmp::msg::c_headerLength +
            lmp::obj::ast::getLength(unknownMessage.m_objects) );
        return length;
      }
      bool operator==(
        const UnknownMessage&  first,
        const UnknownMessage&  second)
      {
        return
//          ( first.m_header == second.m_header &&
//            first.m_objects == second.m_objects );
            true;
      }
      std::ostream& operator<<(
        std::ostream&          os,
        const UnknownMessage&  unknownMessage)
      {
//        std::cout << "UnknownMessage(" << unknownMessage.m_header
//                  << ", " << unknownMessage.m_objects
//                  << ")";
        return os;
      }
    }
  } // namespace msg
} // namespace lmp
