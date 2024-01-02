#ifndef LMP_OBJ_OBJECTSEQUENCE_AST_HPP_
#define LMP_OBJ_OBJECTSEQUENCE_AST_HPP_
/*
 * ObjectSequenceAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectsAst.hpp"

#include <vector>

namespace lmp
{
  namespace obj
  {
    namespace ast
    {
      typedef  std::vector<lmp::obj::ast::Objects>   ObjectSequence;
//    bool operator==(
//      const ObjectSequence&  first,
//      const ObjectSequence&  second);
      std::ostream& operator<<(
        std::ostream&          os,
        const ObjectSequence&  objectSequence);
      template <>
      lmp::DWORD getLength<ObjectSequence>(
        const ObjectSequence&  objectSequence);
//      struct GetLength
//      {
//        template<typename> struct result { typedef lmp::WORD type; };
//        template<typename ObjectSequence>
//        lmp::WORD operator()(
//          const ObjectSequence& objectSequence) const
//        {
//          return getLength(objectSequence);
//        }
//      };
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTSEQUENCE_HPP_ */
