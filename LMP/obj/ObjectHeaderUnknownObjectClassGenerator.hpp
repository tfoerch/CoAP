#ifndef LMP_OBJ_OBJECTHEADER_UNKNOWN_OBJECT_CLASS_GENERATOR_HPP_
#define LMP_OBJ_OBJECTHEADER_UNKNOWN_OBJECT_CLASS_GENERATOR_HPP_
/*
 * ObjectHeaderUnknownObjectClassGenerator.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectHeaderUnknownObjectClassAst.hpp"

//#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
//#include "obj/ByteSequence.hpp"

namespace lmp
{
  namespace obj
  {
    lmp::DWORD getLength(
      const ast::ObjectHeaderUnknownObjectClass&  unknownObjectClass);
    struct GetLengthObjectHeaderUnknownObjectClass
    {
      template<typename> struct result { typedef lmp::WORD type; };
      lmp::WORD operator()(
        const ast::ObjectHeaderUnknownObjectClass& unknownObjectClass) const
      {
        return getLength(unknownObjectClass);
      }
    };
   namespace generator
    {
      namespace karma = boost::spirit::karma;
      template <typename OutputIterator>
      struct object_header_unknown_object_class_grammar : karma::grammar<OutputIterator,
                                                                         ast::ObjectHeaderUnknownObjectClass(lmp::WORD)>
      {
        object_header_unknown_object_class_grammar();

        karma::rule<OutputIterator,
                    ast::ObjectHeaderUnknownObjectClass(lmp::WORD)>             object_header_unknown_object_class_rule;
      };
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTHEADER_UNKNOWN_OBJECT_CLASS_GENERATOR_HPP_ */
