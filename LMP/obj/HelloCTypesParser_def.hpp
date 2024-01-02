#ifndef LMP_OBJ_HELLO_CTYPES_PARSER_DEF_HPP_
#define LMP_OBJ_HELLO_CTYPES_PARSER_DEF_HPP_
/*
 * HelloCTypesParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/HelloCTypesParser.hpp"
#ifdef USE_SPIRIT_X3_PARSER
#include "obj/UnknownHelloCTypeParser_def.hpp"
#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>
#include <boost/spirit/home/x3.hpp>
#else
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/object/static_cast.hpp>
#endif /* USE_SPIRIT_X3_PARSER */

namespace lmp
{
  namespace obj
  {
    namespace hello
    {
      namespace parser
      {
#ifdef USE_SPIRIT_X3_PARSER
        namespace x3 = boost::spirit::x3;
        namespace fusion = boost::fusion;

        ///////////////////////////////////////////////////////////////////////////
        // Rules
        ///////////////////////////////////////////////////////////////////////////

        hello_ctypes_type const hello_ctypes = "hello_ctypes";


        ///////////////////////////////////////////////////////////////////////////
        // Grammar
        ///////////////////////////////////////////////////////////////////////////

        auto const hello_ctypes_def =
          local_cc_id |
          remote_cc_id |
          unknown_cc_id_ctype
          ;

        BOOST_SPIRIT_DEFINE(hello_ctypes);

        ///////////////////////////////////////////////////////////////////////////
        // Annotation and Error handling
        ///////////////////////////////////////////////////////////////////////////

        // We want error-handling only for the start (outermost) rexpr
        // rexpr is the same as rexpr_inner but without error-handling (see error_handler.hpp)
        struct hello_ctypes_class : x3::annotate_on_success/*, error_handler_base*/ {};
#else
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;

        template <typename Iterator>
        hello_ctypes_grammar<Iterator>::hello_ctypes_grammar()
        : hello_ctypes_grammar::base_type(hello_ctypes_rule,
                                                       "hello_ctypes")
        {
          using qi::big_word;
          using qi::big_dword;
          using qi::_1;
          using phoenix::at_c;
          using namespace qi::labels;

          hello_ctypes_rule %=
              hello |
              unknown_hello_ctype
              ;

          hello_ctypes_rule.name("hello_ctypes");
        }
#endif /* USE_SPIRIT_X3_PARSER */
      } // namespace parser

#ifdef USE_SPIRIT_X3_PARSER
      parser::hello_ctypes_type const& hello_ctypes()
      {
        return parser::hello_ctypes;
      }
#endif /* USE_SPIRIT_X3_PARSER */
    } // namespace hello
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLO_CTYPES_PARSER_DEF_HPP_ */
