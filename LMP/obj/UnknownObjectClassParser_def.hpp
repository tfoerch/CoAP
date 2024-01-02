#ifndef LMP_OBJ_UNKNOWN_OBJECT_CLASS_PARSER_DEF_HPP_
#define LMP_OBJ_UNKNOWN_OBJECT_CLASS_PARSER_DEF_HPP_
/*
 * UnknownObjectClassParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/UnknownObjectClassAstAdapted.hpp"
#include "obj/UnknownObjectClassParser.hpp"
#include "obj/ObjectHeaderUnknownObjectClassParser_def.hpp"
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
      using x3::byte_;
      using x3::big_word;
      using x3::get;
      using x3::with;
      using x3::eps;
      using fusion::at_c;

      ///////////////////////////////////////////////////////////////////////////
      // Rule IDs
      ///////////////////////////////////////////////////////////////////////////


      ///////////////////////////////////////////////////////////////////////////
      // Rules
      ///////////////////////////////////////////////////////////////////////////

      unknown_object_class_type const unknown_object_class = "unknown_object_class";


      ///////////////////////////////////////////////////////////////////////////
      // Grammar
      ///////////////////////////////////////////////////////////////////////////
      lmp::WORD unknown_object_class_length;
      // struct ObjLength{}; included from ObjectHeaderUnknownObjectClassParser_def.hpp

      auto header = [&](auto &ctx) { at_c<0>(_val(ctx)) = _attr(ctx); };
      auto push_back = [](auto &ctx) { at_c<1>(_val(ctx)).push_back(_attr(ctx)); };
      auto more   = [](auto &ctx) { _pass(ctx) = get<ObjLength>(ctx) >  at_c<1>(_val(ctx)).size() + lmp::obj::c_objHeaderLength; };
      auto done   = [](auto &ctx) { _pass(ctx) = get<ObjLength>(ctx) == at_c<1>(_val(ctx)).size() + lmp::obj::c_objHeaderLength; };

      auto const unknown_object_class_def =
        with<ObjLength>(std::ref(unknown_object_class_length))
        [
          object_header_unknown_object_class [header]
          >> *( eps [more] >> byte_[push_back] ) >> eps [done] // data
        ];

      BOOST_SPIRIT_DEFINE(unknown_object_class);

      ///////////////////////////////////////////////////////////////////////////
      // Annotation and Error handling
      ///////////////////////////////////////////////////////////////////////////

     // We want error-handling only for the start (outermost) rexpr
      // rexpr is the same as rexpr_inner but without error-handling (see error_handler.hpp)
      struct unknown_object_class_class : x3::annotate_on_success/*, error_handler_base*/ {};
#else
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename Iterator>
      unknown_object_class_grammar<Iterator>::unknown_object_class_grammar()
      : unknown_object_class_grammar::base_type(unknown_object_class_rule, "unknown_object_class_rule")
      {
        using qi::byte_;
        using qi::big_word;
        using qi::_1;
        using qi::eps;
        using qi::repeat;
        using qi::debug;
        using phoenix::at_c;
        using phoenix::push_back;
        using namespace qi::labels;

        unknown_object_class_rule =
            object_header(_a) //[ _1 = at_c<0>(_val) ]
            >> repeat(_a - lmp::obj::c_objHeaderLength)[byte_]
//            >> *( eps(_a > at_c<1>(_val).size() + lmp::obj::c_objHeaderLength)
//                  >> byte_ [push_back(_val, _1)] )
//            >> eps(_a > at_c<1>(_val).size() + lmp::obj::c_objHeaderLength) // [ _1 = at_c<1>(_val) ]
            ;

        unknown_object_class_rule.name("unknown_object_class_rule");

        // debug(unknown_object_class_rule);
      }
#endif /* USE_SPIRIT_X3_PARSER */
    } // namespace parser

#ifdef USE_SPIRIT_X3_PARSER
    parser::unknown_object_class_type const& unknown_object_class()
    {
      return parser::unknown_object_class;
    }
#endif /* USE_SPIRIT_X3_PARSER */
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_UNKNOWN_OBJECT_CLASS_PARSER_DEF_HPP_ */
