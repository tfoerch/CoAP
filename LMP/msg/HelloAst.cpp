/*
 * HelloAst.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "HelloAst.hpp"

namespace lmp
{
  namespace msg
  {
    namespace ast
    {
      lmp::WORD getLength(
        const Hello&  hello)
      {
        return
          ( lmp::msg::c_headerLength +
            lmp::obj::ast::getLength(hello.m_hello)  );
      }
      bool operator==(
        const Hello&  first,
        const Hello&  second)
      {
        return
//          ( first.m_hello == second.m_hello );
            true;
      }
      std::ostream& operator<<(
        std::ostream&  os,
        const Hello&   hello)
      {
//        std::cout << hello.m_hello;
        return os;
      }
    }
  } // namespace msg
} // namespace lmp
