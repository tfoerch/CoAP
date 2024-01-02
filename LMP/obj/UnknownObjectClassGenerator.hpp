#ifndef LMP_OBJ_UNKNOWN_OBJECT_CLASS_GENERATOR_HPP_
#define LMP_OBJ_UNKNOWN_OBJECT_CLASS_GENERATOR_HPP_
/*
 * UnknownObjectClassGenerator.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/UnknownObjectClassAst.hpp"
#include "obj/ObjectHeaderUnknownObjectClassGenerator.hpp"

//#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
//#include "obj/ByteSequence.hpp"

namespace lmp
{
  namespace obj
  {
    namespace generator
    {
      namespace karma = boost::spirit::karma;
      template <typename OutputIterator>
      struct unknown_object_class_grammar : karma::grammar<OutputIterator,
                                                           ast::UnknownObjectClass()>
      {
        unknown_object_class_grammar();

        boost::phoenix::function<ast::GetLength<ast::UnknownObjectClass>>                phx_getLength;
        lmp::obj::generator::object_header_unknown_object_class_grammar<OutputIterator>  object_header;
//        lmp::obj::generate::byte_sequence_grammar<OutputIterator>                        byte_sequence;
        karma::rule<OutputIterator, ast::UnknownObjectClass()>                           unknown_object_class_rule;
      };
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_UNKNOWN_OBJECT_CLASS_GENERATOR_HPP_ */
