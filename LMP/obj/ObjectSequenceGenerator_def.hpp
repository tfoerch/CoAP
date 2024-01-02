#ifndef LMP_OBJ_OBJECTSEQUENCE_DEF_HPP_
#define LMP_OBJ_OBJECTSEQUENCE_DEF_HPP_
/*
 * ObjectSequenceGenerator_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectSequenceGenerator.hpp"
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
    namespace generator
    {
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename OutputIterator>
      object_sequence_grammar<OutputIterator>::object_sequence_grammar()
      : object_sequence_grammar::base_type(object_sequence, "object_sequence")
      {
        using phoenix::at_c;
        using namespace qi::labels;

        object_sequence %=
            +objects
            ;

        object_sequence.name("object_sequence");
      }
    } // namespace generate
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTSEQUENCE_DEF_HPP_ */
