#ifndef LMP_OBJ_HELLO_CTYPES_GENERATOR_DEF_HPP_
#define LMP_OBJ_HELLO_CTYPES_DEF_GENERATOR_HPP_
/*
 * HelloCTypesGenerator_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/HelloCTypesGenerator.hpp"
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/object/static_cast.hpp>

namespace lmp
{
  namespace obj
  {
    namespace hello
    {
      namespace generator
      {
        namespace fusion = boost::fusion;
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;

        template <typename OutputIterator>
        hello_ctypes_grammar<OutputIterator>::hello_ctypes_grammar()
        : hello_ctypes_grammar::base_type(hello_ctypes_rule, "hello_ctypes")
        {
          using phoenix::at_c;
          using namespace qi::labels;

          hello_ctypes_rule %=
              hello |
              unknown_hello_ctype
              ;

          hello_ctypes_rule.name("hello_ctypes");
        }
      } // namespace generate
    } // namespace hello
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLO_CTYPES_GENERATOR_DEF_HPP_ */
