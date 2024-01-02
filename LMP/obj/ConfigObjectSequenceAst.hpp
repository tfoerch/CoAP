#ifndef LMP_OBJ_CONFIG_OBJECT_SEQUENCE_AST_HPP_
#define LMP_OBJ_CONFIG_OBJECT_SEQUENCE_AST_HPP_
/*
 * ConfigObjectSequenceAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ConfigCTypesAst.hpp"

#include <vector>

namespace lmp
{
  namespace obj
  {
    namespace config
    {
      namespace ast
      {
        typedef std::vector<lmp::obj::config::ast::ConfigCTypes>  ConfigObjectSequence;
      }
    }
    namespace ast
    {
      std::ostream& operator<<(
        std::ostream&                             os,
        const config::ast::ConfigObjectSequence&  configObjectSequence);
      template <>
      lmp::DWORD getLength<config::ast::ConfigObjectSequence>(
        const config::ast::ConfigObjectSequence&  configObjectSequence);
//      struct GetLength
//      {
//        template<typename> struct result { typedef lmp::WORD type; };
//        template<typename ConfigObjectSequence>
//        lmp::WORD operator()(
//          const ConfigObjectSequence& configObjectSequence) const
//        {
//          return getLength(configObjectSequence);
//        }
//      };
    }

  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_CONFIG_OBJECT_SEQUENCE_AST_HPP_ */
