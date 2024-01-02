#ifndef LMP_OBJ_CONFIG_OBJECT_SEQUENCE_PARSER_HPP_
#define LMP_OBJ_CONFIG_OBJECT_SEQUENCE_PARSER_HPP_
/*
 * ConfigObjectSequenceParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ConfigObjectSequenceAst.hpp"
#include "obj/ConfigCTypesParser.hpp"

#include <boost/spirit/include/qi.hpp>

namespace lmp
{
  namespace obj
  {
    namespace config
    {
      namespace parser
      {
        namespace qi = boost::spirit::qi;
        template <typename Iterator>
        struct config_object_sequence_grammar : qi::grammar<Iterator,
                                                            ast::ConfigObjectSequence(lmp::WORD)>
        {
          config_object_sequence_grammar();

          boost::phoenix::function<lmp::obj::ast::GetLength<ast::ConfigObjectSequence>>  phx_getLength;
          lmp::obj::config::parser::config_ctypes_grammar<Iterator>            config_object;
          qi::rule<Iterator,
                   ast::ConfigObjectSequence(lmp::WORD)>                       config_object_sequence;
        };
      }
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_CONFIG_OBJECT_SEQUENCE_PARSER_HPP_ */
