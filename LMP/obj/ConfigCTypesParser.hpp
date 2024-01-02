#ifndef LMP_OBJ_CONFIG_CTYPES_PARSER_HPP_
#define LMP_OBJ_CONFIG_CTYPES_PARSER_HPP_
/*
 * ConfigCTypesParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ConfigCTypesAst.hpp"

#ifdef USE_SPIRIT_X3_PARSER
#include <boost/spirit/home/x3/support/traits/is_variant.hpp>
#include <boost/spirit/home/x3/support/traits/tuple_traits.hpp>
#include <boost/spirit/home/x3/nonterminal/rule.hpp>
#else
#include "obj/HelloConfigParser.hpp"
#include "obj/ObjectClassUnknownCTypeParser.hpp"
#include <boost/spirit/include/qi.hpp>
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

        struct config_ctypes_class;
        typedef
          x3::rule<config_ctypes_class, config::ast::ConfigCTypes>  config_ctypes_type;
        BOOST_SPIRIT_DECLARE(config_ctypes_type);
#else

        namespace qi = boost::spirit::qi;
        template <typename Iterator>
        struct config_ctypes_grammar : qi::grammar<Iterator, config::ast::ConfigCTypes()>
        {
          config_ctypes_grammar();

          lmp::obj::parser::hello_config_grammar<Iterator>                             hello_config;
          lmp::obj::parser::object_class_unknown_ctype_grammar<Iterator,
                                                               ObjectClass::Config>    unknown_config_ctype;
          qi::rule<Iterator, config::ast::ConfigCTypes()>                              config_ctypes_rule;
        };
#endif /* USE_SPIRIT_X3_PARSER */
      }
#ifdef USE_SPIRIT_X3_PARSER
      parser::config_ctypes_type const& config_ctypes();
#endif /* USE_SPIRIT_X3_PARSER */
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_CONFIG_CTYPES_PARSER_HPP_ */
