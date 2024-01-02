#ifndef LMP_OBJ_HELLO_CONFIG_PARSER_DEF_HPP_
#define LMP_OBJ_HELLO_CONFIG_PARSER_DEF_HPP_
/*
 * HelloConfigParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/HelloConfigAstAdapted.hpp"
#include "obj/HelloConfigParser.hpp"
#include "obj/ObjectClassAst.hpp"
#ifdef USE_SPIRIT_X3_PARSER
#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>
#include <boost/spirit/home/x3/binary/binary.hpp>
#include <boost/spirit/home/x3.hpp>
#else
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/object/static_cast.hpp>
#endif /* USE_SPIRIT_X3_PARSER */

#include <type_traits>

namespace lmp
{
  namespace obj
  {
    namespace parser
    {
#ifdef USE_SPIRIT_X3_PARSER
      namespace x3 = boost::spirit::x3;
      namespace fusion = boost::fusion;
      using x3::big_word;
      using x3::get;
      using x3::with;
      using fusion::at_c;

      ///////////////////////////////////////////////////////////////////////////
      // Rules
      ///////////////////////////////////////////////////////////////////////////

      hello_config_type const hello_config = "hello_config";


      ///////////////////////////////////////////////////////////////////////////
      // Grammar
      ///////////////////////////////////////////////////////////////////////////
//      lmp::WORD var_obj_length;

      auto header = [&](auto &ctx) { at_c<0>(_val(ctx)) = _attr(ctx); };
      auto ccId = [](auto &ctx) { at_c<1>(_val(ctx)) = _attr(ctx); };
      auto checkLength = [](auto &ctx) { _pass(ctx) = get<ObjLength>(ctx) == HeaderCTypeTraits<config::ClassType, config::ClassType::HelloConfig>::length; };

//      auto const hello_config_def =
//        with<ObjLength>(std::ref(var_obj_length))
//        [
//          object_header_var_length<config::ClassType, config::ClassType::HelloConfig> [header]
//          >> eps [checkLength]
//          >> big_dword [ccId]
//        ];

      auto const hello_config_def =
        object_header_fix_length<config::ClassType, config::ClassType::HelloConfig> // [header]
        >> big_word //[helloIntv]
        >> big_word //[helloDeadIntv]
        ;

      BOOST_SPIRIT_DEFINE(hello_config);

      ///////////////////////////////////////////////////////////////////////////
      // Annotation and Error handling
      ///////////////////////////////////////////////////////////////////////////

      // We want error-handling only for the start (outermost) rexpr
      // rexpr is the same as rexpr_inner but without error-handling (see error_handler.hpp)
      struct hello_config_class : x3::annotate_on_success/*, error_handler_base*/ {};
#else
      namespace qi = boost::spirit::qi;
      template <typename Iterator>
      hello_config_grammar<Iterator>::hello_config_grammar()
      : hello_config_grammar::base_type(hello_config_rule,
                                       "hello_config")
      {
        using qi::big_word;
        using qi::_1;
        // using phoenix::at_c;
        using namespace qi::labels;

        hello_config_rule =
          object_header
          >> big_word //[helloIntv]
          >> big_word //[helloDeadIntv]
          ;

        hello_config_rule.name("hello_config");
      }
#endif /* USE_SPIRIT_X3_PARSER */
    } // namespace parser

#ifdef USE_SPIRIT_X3_PARSER
    parser::hello_config_type const& hello_config()
    {
      return parser::hello_config;
    }
#endif /* USE_SPIRIT_X3_PARSER */
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLO_CONFIG_PARSER_DEF_HPP_ */
