#ifndef LMP_OBJ_HELLO_CTYPES_GENERATOR_HPP_
#define LMP_OBJ_HELLO_CTYPES_GENERATOR_HPP_
/*
 * HelloCTypesGenerator.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/HelloGenerator.hpp"
#include "obj/ObjectClassUnknownCTypeGenerator.hpp"
#include "obj/HelloCTypesAst.hpp"

#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace obj
  {
    namespace hello
    {
      lmp::DWORD getLength(
        const ast::HelloCTypes&  controlChannelIdCTypes);
      std::ostream& operator<<(
        std::ostream&                       os,
        const ast::HelloCTypes&  controlChannelIdCTypes);
      namespace generator
      {
        namespace karma = boost::spirit::karma;
        template <typename OutputIterator>
        struct hello_ctypes_grammar : karma::grammar<OutputIterator, ast::HelloCTypes()>
        {
          hello_ctypes_grammar();

          lmp::obj::generator::hello_grammar<OutputIterator>                                    hello;
          lmp::obj::generator::object_class_unknown_ctype_grammar<OutputIterator,
                                                                 lmp::obj::ObjectClass::Hello>  unknown_hello_ctype;
          karma::rule<OutputIterator, ast::HelloCTypes()>                                       hello_ctypes_rule;
        };
      }
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLO_CTYPES_GENERATOR_HPP_ */
