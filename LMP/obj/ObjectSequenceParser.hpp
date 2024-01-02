#ifndef LMP_OBJ_OBJECTSEQUENCE_PARSER_HPP_
#define LMP_OBJ_OBJECTSEQUENCE_PARSER_HPP_
/*
 * ObjectSequenceParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectSequenceAst.hpp"
#include "obj/ObjectsParser.hpp"

#include <boost/spirit/include/qi.hpp>

namespace lmp
{
  namespace obj
  {
    namespace parser
    {
      namespace qi = boost::spirit::qi;
      template <typename Iterator>
      struct object_sequence_grammar : qi::grammar<Iterator,
                                                   ast::ObjectSequence(lmp::WORD)>
      {
        object_sequence_grammar();

        boost::phoenix::function<ast::GetLength<ast::ObjectSequence>>         phx_getLength;
        lmp::obj::parser::objects_grammar<Iterator>      objects;
        qi::rule<Iterator,
                 ast::ObjectSequence(lmp::WORD)>         object_sequence;
      };
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTSEQUENCE_PARSER_HPP_ */
