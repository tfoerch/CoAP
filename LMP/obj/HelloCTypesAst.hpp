#ifndef LMP_OBJ_HELLO_CTYPES_HPP_
#define LMP_OBJ_HELLO_CTYPES_HPP_
/*
 * HelloCTypesAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/HelloAst.hpp"
#include "obj/UnknownHelloCTypeAst.hpp"

#include <boost/variant.hpp>

namespace lmp
{
  namespace obj
  {
    namespace hello
    {
      namespace ast
      {
         typedef boost::variant<lmp::obj::hello::ast::Hello,
                                lmp::obj::hello::ast::UnknownHelloCType>   HelloCTypes;
         std::ostream& operator<<(
           std::ostream&       os,
           const HelloCTypes&  helloCType);
      }
    }
    namespace ast
    {
      template <>
      lmp::DWORD getBodyLength<hello::ast::HelloCTypes>(
        const hello::ast::HelloCTypes&  helloCType);
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLO_CTYPES_HPP_ */
