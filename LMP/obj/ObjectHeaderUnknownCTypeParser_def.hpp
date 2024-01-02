#ifndef LMP_OBJ_OBJECTHEADER_UNKNOWN_CTYPE_PARSER_DEF_HPP_
#define LMP_OBJ_OBJECTHEADER_UNKNOWN_CTYPE_PARSER_DEF_HPP_
/*
 * ObjectHeaderUnknownCTypeParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectHeaderUnknownCTypeAstAdapted.hpp"
#include "obj/ObjectHeaderUnknownCTypeParser.hpp"

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
      using x3::omit;
      using x3::eps;
      using x3::with;
      using fusion::at_c;

      ///////////////////////////////////////////////////////////////////////////
      // Rule IDs
      ///////////////////////////////////////////////////////////////////////////

      ///////////////////////////////////////////////////////////////////////////
      // Rules
      ///////////////////////////////////////////////////////////////////////////

      template <ObjectClass objClass>
      object_header_unknown_ctype_type<objClass> const
        object_header_unknown_ctype = "object_header_unknown_ctype";


      ///////////////////////////////////////////////////////////////////////////
      // Grammar
      ///////////////////////////////////////////////////////////////////////////

      auto classTypeAndNeg = [](auto &ctx) { at_c<0>(_val(ctx)) = ( _attr(ctx) & lmp::obj::c_classTypeMask); at_c<1>(_val(ctx)) = ( _attr(ctx) & lmp::obj::c_negotiableMask); };
      auto length = [](auto &ctx) { get<ObjLength>(ctx).get() = _attr(ctx); };

      template <ObjectClass objClass>
      auto const object_header_unknown_ctype_def =
          byte_[classTypeAndNeg]  // class type
          >> byte_(static_cast<typename std::underlying_type<ObjectClass>::type>(objClass))      // object class
          >> big_word [length]     // length
          ;

      template <typename Iterator, typename Context, typename Attribute, ObjectClass objClass>
      inline bool parse_rule( object_header_unknown_ctype_type<objClass> rule, Iterator& first, Iterator const& last , Context const& context, Attribute& attr)
      {
        using boost::spirit::x3::unused;
        static auto const def_ = (object_header_unknown_ctype<objClass> = object_header_unknown_ctype_def<objClass>);
        return def_.parse(first, last, context, unused, attr);
      }
      // BOOST_SPIRIT_DEFINE(object_header_unknown_ctype_inner, object_header_unknown_ctype);

      ///////////////////////////////////////////////////////////////////////////
      // Annotation and Error handling
      ///////////////////////////////////////////////////////////////////////////

      // We want error-handling only for the start (outermost) rexpr
      // rexpr is the same as rexpr_inner but without error-handling (see error_handler.hpp)
      struct object_header_unknown_ctype_class : x3::annotate_on_success/*, error_handler_base*/ {};
#else
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename Iterator, ObjectClass objClass>
      object_header_unknown_ctype_grammar<Iterator, objClass>::object_header_unknown_ctype_grammar()
      : object_header_unknown_ctype_grammar::base_type(object_header_unknown_ctype_rule, "object_header_unknown_ctype")
      {
        using qi::byte_;
        using qi::big_word;
        using qi::_1;
        using phoenix::at_c;
        using namespace qi::labels;

        object_header_unknown_ctype_rule =
            byte_ [at_c<0>(_val) = (_1 & lmp::obj::c_classTypeMask), at_c<1>(_val) = (_1 & lmp::obj::c_negotiableMask) ]  // class type
            >> byte_(static_cast<typename std::underlying_type<ObjectClass>::type>(objClass))    // object class
            >> big_word [_r1 = _1] // length
            ;

        object_header_unknown_ctype_rule.name("object_header_unknown_ctype");
      }
#endif /* USE_SPIRIT_X3_PARSER */
    } // namespace parser
#ifdef USE_SPIRIT_X3_PARSER
    template <ObjectClass objClass>
    parser::object_header_unknown_ctype_type<objClass> const& object_header_unknown_ctype()
    {
      return parser::object_header_unknown_ctype<objClass>;
    }
#endif /* USE_SPIRIT_X3_PARSER */
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTHEADER_UNKNOWN_CTYPE_PARSER_DEF_HPP_ */
