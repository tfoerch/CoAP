#ifndef LMP_OBJ_OBJECTHEADER_UNKNOWN_CTYPE_GENERATOR_HPP_
#define LMP_OBJ_OBJECTHEADER_UNKNOWN_CTYPE_GENERATOR_HPP_
/*
 * ObjectHeaderUnknownCTypeGenerator.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectHeaderUnknownCTypeAst.hpp"
#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace obj
  {
    template <typename  ObjClassTraits>
    lmp::DWORD getLength(
      const ast::ObjectHeaderUnknownCType<ObjClassTraits>&  objectClassUnknownCType);
    template<typename ObjClassTraits>
    struct GetLengthUnknownCTypeData
    {
      template<typename> struct result { typedef lmp::WORD type; };
      lmp::WORD operator()(
        const ast::ObjectHeaderUnknownCType<ObjClassTraits>& objClassUnknownCTypeData) const
      {
        return getLength(objClassUnknownCTypeData);
      }
    };
    namespace generator
    {
      namespace karma = boost::spirit::karma;
      template <typename OutputIterator, ObjectClass objClass>
      struct object_header_unknown_ctype_grammar : karma::grammar<OutputIterator,
                                                                 ast::ObjectHeaderUnknownCType<ObjectClassTraits<objClass>>(lmp::WORD)>
      {
        object_header_unknown_ctype_grammar();

        karma::rule<OutputIterator,
                    ast::ObjectHeaderUnknownCType<ObjectClassTraits<objClass>>(lmp::WORD)>  object_header_unknown_ctype_rule;
      };
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTHEADER_UNKNOWN_CTYPE_GENERATOR_HPP_ */
