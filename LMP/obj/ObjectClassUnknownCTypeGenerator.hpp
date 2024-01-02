#ifndef LMP_OBJ_OBJECTCLASS_UNKNOWN_CTYPE_GENERATOR_HPP_
#define LMP_OBJ_OBJECTCLASS_UNKNOWN_CTYPE_GENERATOR_HPP_
/*
 * ObjectClassUnknownCTypeGenerator.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectClassUnknownCTypeAst.hpp"
#include "obj/ObjectHeaderUnknownCTypeGenerator.hpp"
#include <boost/spirit/include/karma.hpp>
//#include "obj/ByteSequence.hpp"

namespace lmp
{
  namespace obj
  {
    namespace generator
    {
      namespace karma = boost::spirit::karma;
      template <typename OutputIterator, ObjectClass objClass>
      struct object_class_unknown_ctype_grammar : karma::grammar<OutputIterator, ast::ObjectClassUnknownCType<ObjectClassTraits<objClass>>()>
      {
        object_class_unknown_ctype_grammar();

        boost::phoenix::function<ast::GetLength<ast::ObjectClassUnknownCType<ObjectClassTraits<objClass>>>>  phx_getLength;
        lmp::obj::generator::object_header_unknown_ctype_grammar<OutputIterator, objClass>        object_header;
//        lmp::obj::generate::byte_sequence_grammar<OutputIterator>                                 byte_sequence;
        karma::rule<OutputIterator, ast::ObjectClassUnknownCType<ObjectClassTraits<objClass>>()>  object_class_unknown_ctype_rule;
      };
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTCLASS_UNKNOWN_CTYPE_GENERATOR_HPP_ */
