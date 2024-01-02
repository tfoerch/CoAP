#ifndef LMP_OBJ_OBJECTSEQUENCE_GENERATOR_HPP_
#define LMP_OBJ_OBJECTSEQUENCE_GENERATOR_HPP_
/*
 * ObjectSequenceGenerator.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectSequenceAst.hpp"
#include "obj/ObjectsGenerator.hpp"
#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace obj
  {
    namespace generator
    {
      namespace karma = boost::spirit::karma;
      template <typename OutputIterator>
      struct object_sequence_grammar : karma::grammar<OutputIterator, ast::ObjectSequence()>
      {
        object_sequence_grammar();

        lmp::obj::generator::objects_grammar<OutputIterator>   objects;
        karma::rule<OutputIterator, ast::ObjectSequence()>    object_sequence;
      };
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTSEQUENCE_GENERATOR_HPP_ */
