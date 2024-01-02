#ifndef LMP_OBJ_OBJECTHEADER_PARSER_HPP_
#define LMP_OBJ_OBJECTHEADER_PARSER_HPP_
/*
 * ObjectHeaderParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectHeaderAst.hpp"

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

      struct object_header_fix_length_class;
      template <typename ClassType, ClassType ctype>
      using object_header_fix_length_type =
        x3::rule<object_header_fix_length_class, ast::ObjectHeader<HeaderCTypeTraits<ClassType, ctype> > >;
      // BOOST_SPIRIT_DECLARE(object_header_fix_length_type);
      template <typename Iterator, typename Context, typename Attribute, typename ClassType, ClassType ctype>
      bool parse_rule(object_header_fix_length_type<ClassType, ctype> rule,
                      Iterator&       first,
                      Iterator const& last,
                      Context const&  context,
                      Attribute&      attr);

      struct object_header_var_length_class;
      template <typename ClassType, ClassType ctype>
      using object_header_var_length_type =
        x3::rule<object_header_var_length_class, ast::ObjectHeader<HeaderCTypeTraits<ClassType, ctype> > >;
      // BOOST_SPIRIT_DECLARE(object_header_var_length_type);
      template <typename Iterator, typename Context, typename Attribute, typename ClassType, ClassType ctype>
      bool parse_rule(object_header_var_length_type<ClassType, ctype> rule,
                      Iterator&       first,
                      Iterator const& last,
                      Context const&  context,
                      Attribute&      attr);
#else
      namespace qi = boost::spirit::qi;

      template <typename Iterator, typename ClassType, ClassType ctype>
      struct object_header_fix_length_grammar : qi::grammar<Iterator, ast::ObjectHeader<HeaderCTypeTraits<ClassType, ctype> >()>
      {
        object_header_fix_length_grammar();
        qi::rule<Iterator, ast::ObjectHeader<HeaderCTypeTraits<ClassType, ctype> >()>                object_header_fix_length_rule;
      };

      template <typename Iterator, typename ClassType, ClassType ctype>
      struct object_header_var_length_grammar : qi::grammar<Iterator, ast::ObjectHeader<HeaderCTypeTraits<ClassType, ctype> >(lmp::WORD&)>
      {
        object_header_var_length_grammar();
        qi::rule<Iterator, ast::ObjectHeader<HeaderCTypeTraits<ClassType, ctype> >(lmp::WORD&)>                object_header_var_length_rule;
      };

#endif /* USE_SPIRIT_X3_PARSER */
    }
#ifdef USE_SPIRIT_X3_PARSER
    template <typename ClassType, ClassType ctype>
    parser::object_header_fix_length_type<ClassType, ctype> const& object_header_fix_length();
    template <typename ClassType, ClassType ctype>
    parser::object_header_var_length_type<ClassType, ctype> const& object_header_var_length();
#endif /* USE_SPIRIT_X3_PARSER */
  } // namespace obj
} // namespace lmp


#endif /* LMP_OBJ_OBJECTHEADER_PARSER_HPP_ */
