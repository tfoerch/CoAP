#ifndef LMP_OBJ_HELLO_GENERATOR_DEF_HPP_
#define LMP_OBJ_HELLO_GENERATOR_DEF_HPP_
/*
 * HelloGenerator_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/HelloAstAdapted.hpp"
#include "obj/HelloGenerator.hpp"
#include "obj/ObjectClassAst.hpp"
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/object/static_cast.hpp>

#include <type_traits>

namespace lmp
{
  namespace obj
  {
//    lmp::DWORD getLength(
//      const hello::ast::Hello&  localHello)
//    {
//      return
//        ( c_objHeaderLength +
//          localHello.m_data.size() );
//    }
    namespace generator
    {
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename OutputIterator>
      hello_grammar<OutputIterator>::hello_grammar()
      : hello_grammar::base_type(hello_rule, "hello")
      {
        using qi::byte_;
        using qi::big_dword;
        using qi::eps;
        using phoenix::at_c;
        using namespace qi::labels;

        hello_rule =
            object_header(phx_getLength(_val)) [ _1 = at_c<0>(_val) ]
            << big_dword [ _1 = at_c<1>(_val) ]
            ;

        hello_rule.name("hello");
      }
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLO_GENERATOR_DEF_HPP_ */
