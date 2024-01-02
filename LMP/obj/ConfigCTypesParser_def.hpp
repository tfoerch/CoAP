#ifndef LMP_OBJ_CONFIG_CTYPES_PARSER_DEF_HPP_
#define LMP_OBJ_CONFIG_CTYPES_PARSER_DEF_HPP_
/*
 * ConfigCTypesParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ConfigCTypesParser.hpp"
#ifdef USE_SPIRIT_X3_PARSER
#include "obj/UnknownConfigCTypeParser_def.hpp"
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
    namespace config
    {
      namespace parser
      {
#ifdef USE_SPIRIT_X3_PARSER
        namespace x3 = boost::spirit::x3;
        namespace fusion = boost::fusion;

        ///////////////////////////////////////////////////////////////////////////
        // Rules
        ///////////////////////////////////////////////////////////////////////////

        config_ctypes_type const config_ctypes = "config_ctypes";


        ///////////////////////////////////////////////////////////////////////////
        // Grammar
        ///////////////////////////////////////////////////////////////////////////

        auto const config_ctypes_def =
          hello_config |
          config_ctypes_rule
          ;

        BOOST_SPIRIT_DEFINE(config_ctypes);

        ///////////////////////////////////////////////////////////////////////////
        // Annotation and Error handling
        ///////////////////////////////////////////////////////////////////////////

        // We want error-handling only for the start (outermost) rexpr
        // rexpr is the same as rexpr_inner but without error-handling (see error_handler.hpp)
        struct config_ctypes_class : x3::annotate_on_success/*, error_handler_base*/ {};
#else
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;

        template <typename Iterator>
        config_ctypes_grammar<Iterator>::config_ctypes_grammar()
        : config_ctypes_grammar::base_type(config_ctypes_rule,
                                                       "config_ctypes")
        {
          using qi::big_word;
          using qi::big_dword;
          using qi::_1;
          using phoenix::at_c;
          using namespace qi::labels;

          config_ctypes_rule %=
              hello_config |
              unknown_config_ctype
              ;

          config_ctypes_rule.name("config_ctypes");
        }
#endif /* USE_SPIRIT_X3_PARSER */
      } // namespace parser

#ifdef USE_SPIRIT_X3_PARSER
      parser::config_ctypes_type const& config_ctypes()
      {
        return parser::config_ctypes;
      }
#endif /* USE_SPIRIT_X3_PARSER */
    } // namespace config
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_CONFIG_CTYPES_PARSER_DEF_HPP_ */
