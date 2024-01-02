#ifndef LMP_OBJ_OBJECTSEQUENCE_PARSER_DEF_HPP_
#define LMP_OBJ_OBJECTSEQUENCE_PARSER_DEF_HPP_
/*
 * ObjectSequenceParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectSequenceParser.hpp"
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/object/static_cast.hpp>

namespace lmp
{
  namespace obj
  {
    namespace parser
    {
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename Iterator>
      object_sequence_grammar<Iterator>::object_sequence_grammar()
      : object_sequence_grammar::base_type(object_sequence,
                                           "object_sequence")
      {
        using qi::_1;
        using qi::eps;
        // using qi::debug;
        using phoenix::at_c;
        using phoenix::push_back;
        using namespace qi::labels;

        object_sequence =
            objects [ push_back(_val, _1)]
            >> *( eps (_r1 >= phx_getLength(_val)) >> objects[push_back(_val, _1)] ) >> eps (_r1 == phx_getLength(_val))
            ;

        object_sequence.name("object_sequence");

        // debug(object_sequence);
      }
    } // namespace parse
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTSEQUENCE_PARSER_DEF_HPP_ */
