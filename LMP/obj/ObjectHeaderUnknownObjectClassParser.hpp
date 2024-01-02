#ifndef LMP_OBJ_OBJECTHEADER_UNKNOWN_OBJECT_CLASS_PARSER_HPP_
#define LMP_OBJ_OBJECTHEADER_UNKNOWN_OBJECT_CLASS_PARSER_HPP_
/*
 * ObjectHeaderUnknownObjectClassParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectHeaderUnknownObjectClassAst.hpp"

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

      struct object_header_unknown_object_class_class;
      typedef
        x3::rule<object_header_unknown_object_class_class, ast::ObjectHeaderUnknownObjectClass>  object_header_unknown_object_class_type;
      BOOST_SPIRIT_DECLARE(object_header_unknown_object_class_type);
#else
      namespace qi = boost::spirit::qi;

      template <typename Iterator>
      struct object_header_unknown_object_class_grammar : qi::grammar<Iterator, ast::ObjectHeaderUnknownObjectClass(lmp::WORD&)>
      {
        object_header_unknown_object_class_grammar();
        qi::rule<Iterator, ast::ObjectHeaderUnknownObjectClass(lmp::WORD&)>                object_header_unknown_object_class_rule;
      };

#endif /* USE_SPIRIT_X3_PARSER */
    }
#ifdef USE_SPIRIT_X3_PARSER
    parser::object_header_unknown_object_class_type const& object_header_unknown_object_class();
#endif /* USE_SPIRIT_X3_PARSER */
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTHEADER_UNKNOWN_OBJECT_CLASS_PARSER_HPP_ */
