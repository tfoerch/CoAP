#ifndef LMP_OBJ_OBJECTHEADER_UNKNOWN_OBJECT_CLASS_PARSER_DEF_HPP_
#define LMP_OBJ_OBJECTHEADER_UNKNOWN_OBJECT_CLASS_PARSER_DEF_HPP_
/*
 * ObjectHeaderUnknownObjectClassParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectHeaderUnknownObjectClassAstAdapted.hpp"
#include "obj/ObjectHeaderUnknownObjectClassParser.hpp"
#include "obj/ObjectClassAst.hpp"

#ifdef USE_SPIRIT_X3_PARSER
#include "obj/LMPParseConfig.hpp"
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

      object_header_unknown_object_class_type const object_header_unknown_object_class = "object_header_unknown_object_class";


      ///////////////////////////////////////////////////////////////////////////
      // Grammar
      ///////////////////////////////////////////////////////////////////////////

      auto objclass = [](auto &ctx) { at_c<0>(_val(ctx)) = _attr(ctx); };
      auto classTypeAndNeg = [](auto &ctx) { at_c<1>(_val(ctx)) = static_cast<lmp::BYTE>( _attr(ctx) & lmp::obj::c_classTypeMask); at_c<2>(_val(ctx)) = ( _attr(ctx) & lmp::obj::c_negotiableMask); };
      auto length = [](auto &ctx) { get<ObjLength>(ctx).get() = _attr(ctx); };

      auto const object_header_unknown_object_class_def =
          byte_ [classTypeAndNeg]  // class type
          >> byte_ [objclass]      // object class
          >> big_word [length]     // length
          ;


      BOOST_SPIRIT_DEFINE(object_header_unknown_object_class);

      ///////////////////////////////////////////////////////////////////////////
      // Annotation and Error handling
      ///////////////////////////////////////////////////////////////////////////

      // We want error-handling only for the start (outermost) rexpr
      // rexpr is the same as rexpr_inner but without error-handling (see error_handler.hpp)
      struct object_header_unknown_object_class_class : x3::annotate_on_success/*, error_handler_base*/ {};
#else
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename Iterator>
      object_header_unknown_object_class_grammar<Iterator>::object_header_unknown_object_class_grammar()
      : object_header_unknown_object_class_grammar::base_type(object_header_unknown_object_class_rule, "object_header_unknown_object_class")
      {
        using qi::byte_;
        using qi::big_word;
        using qi::_1;
        using qi::debug;
        using phoenix::at_c;
        using namespace qi::labels;

        object_header_unknown_object_class_rule =
            byte_ [at_c<1>(_val) = (_1 & lmp::obj::c_classTypeMask), at_c<2>(_val) = (_1 & lmp::obj::c_negotiableMask) ]  // class type
            >> byte_ [at_c<0>(_val) = _1]    // object class
            >> big_word [_r1 = _1] // length
            ;

        object_header_unknown_object_class_rule.name("object_header_unknown_object_class");

        //debug(object_header_unknown_object_class_rule);
      }
#endif /* USE_SPIRIT_X3_PARSER */
    } // namespace parser

#ifdef USE_SPIRIT_X3_PARSER
    parser::object_header_unknown_object_class_type const& object_header_unknown_object_class()
    {
      return parser::object_header_unknown_object_class;
    }
#endif /* USE_SPIRIT_X3_PARSER */
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTHEADER_UNKNOWN_OBJECT_CLASS_PARSER_DEF_HPP_ */
