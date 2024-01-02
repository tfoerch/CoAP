#ifndef LMP_OBJ_UNKNOWN_OBJECT_CLASS_AST_HPP_
#define LMP_OBJ_UNKNOWN_OBJECT_CLASS_AST_HPP_
/*
 * UnknownObjectClassAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectHeaderUnknownObjectClassAst.hpp"
#include "obj/ObjectClassAst.hpp"

#include <iostream>

#ifdef USE_SPIRIT_X3_PARSER
#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#endif /* USE_SPIRIT_X3_PARSER */

#include <vector>

namespace lmp
{
  namespace obj
  {
    namespace ast
    {
#ifdef USE_SPIRIT_X3_PARSER
      namespace x3 = boost::spirit::x3;
#endif /* USE_SPIRIT_X3_PARSER */

      typedef std::vector<lmp::BYTE>  ByteSequence;

      struct UnknownObjectClass
#ifdef USE_SPIRIT_X3_PARSER
          : x3::position_tagged
#endif /* USE_SPIRIT_X3_PARSER */
      {
        ObjectHeaderUnknownObjectClass  m_header;
        ByteSequence                    m_data;
      };
      std::ostream& operator<<(
        std::ostream&   os,
        const UnknownObjectClass&  object);
      template <>
      lmp::DWORD getBodyLength<UnknownObjectClass>(
        const UnknownObjectClass&  object);

//      lmp::DWORD getLength(
//        const ast::UnknownObjectClass&  unknownObjectClass);
//      struct GetLengthUnknownObjectClass
//      {
//        template<typename> struct result { typedef lmp::WORD type; };
//        lmp::WORD operator()(
//          const ast::UnknownObjectClass& unknownObjectClass) const
//        {
//          return getLength(unknownObjectClass);
//        }
//      };
    } // namespace ast
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_UNKNOWN_OBJECT_CLASS__AST_HPP_ */
