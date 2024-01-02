#ifndef LMP_OBJ_OBJECTHEADER_UNKNOWN_CTYPE_PARSER_HPP_
#define LMP_OBJ_OBJECTHEADER_UNKNOWN_CTYPE_PARSER_HPP_
/*
 * ObjectHeaderUnknownCTypeParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectHeaderUnknownCTypeAst.hpp"

#ifdef USE_SPIRIT_X3_PARSER
#include <boost/spirit/home/x3/support/traits/is_variant.hpp>
#include <boost/spirit/home/x3/support/traits/tuple_traits.hpp>
#include <boost/spirit/home/x3/nonterminal/rule.hpp>
#else
#include <boost/spirit/include/qi.hpp>
#endif /* USE_SPIRIT_X3_PARSER */

namespace lmp
{
  namespace obj
  {
    namespace parser
    {
#ifdef USE_SPIRIT_X3_PARSER
      namespace x3 = boost::spirit::x3;

      struct object_header_unknown_ctype_class;
      template <ObjectClass objClass>
      using object_header_unknown_ctype_type =
        x3::rule<object_header_unknown_ctype_class, ast::ObjectHeaderUnknownCType<ObjectClassTraits<objClass>>>;
      // BOOST_SPIRIT_DECLARE(object_header_unknown_ctype_type);
      template <typename Iterator, typename Context, typename Attribute, ObjectClass objClass>
      bool parse_rule(object_header_unknown_ctype_type<objClass> rule,
                      Iterator&       first,
                      Iterator const& last,
                      Context const& context,
                      Attribute& attr);
#else
      namespace qi = boost::spirit::qi;

      template <typename Iterator, ObjectClass objClass>
      struct object_header_unknown_ctype_grammar : qi::grammar<Iterator, ast::ObjectHeaderUnknownCType<ObjectClassTraits<objClass>>(lmp::WORD&)>
      {
        object_header_unknown_ctype_grammar();
        qi::rule<Iterator, ast::ObjectHeaderUnknownCType<ObjectClassTraits<objClass>>(lmp::WORD&)>                object_header_unknown_ctype_rule;
      };

#endif /* USE_SPIRIT_X3_PARSER */
    }
#ifdef USE_SPIRIT_X3_PARSER
    template <ObjectClass objClass>
    parser::object_header_unknown_ctype_type<objClass> const& object_header_unknown_ctype();
#endif /* USE_SPIRIT_X3_PARSER */
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTHEADER_UNKNOWN_CTYPE_PARSER_HPP_ */
