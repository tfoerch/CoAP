/*
 * ObjectSequenceAst.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectSequenceAst.hpp"

namespace lmp
{
  namespace obj
  {
    namespace ast
    {
      template <>
      lmp::DWORD getLength<ObjectSequence>(
        const ObjectSequence&  objectSequence)
      {
        lmp::DWORD length = 0;
        for (std::vector<Objects>::const_iterator iter = objectSequence.begin();
             iter != objectSequence.end();
             ++iter)
        {
          length += getLength(*iter);
        }
        // std::cout << length << std::endl;
        return length;
      }

      std::ostream& operator<<(
        std::ostream&          os,
        const ObjectSequence&  objectSequence)
      {
        for (std::vector<lmp::obj::ast::Objects>::const_iterator iter = objectSequence.begin();
             iter != objectSequence.end();
             ++iter)
        {
          if (iter != objectSequence.begin())
          {
            os << ", ";
          }
          os << *iter;
        }
        return os;
      }
    }
  } // namespace obj
} // namespace lmp
