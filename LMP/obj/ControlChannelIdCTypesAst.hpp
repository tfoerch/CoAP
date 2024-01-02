#ifndef LMP_OBJ_CC_ID_CTYPES_HPP_
#define LMP_OBJ_CC_ID_CTYPES_HPP_
/*
 * ControlChannelIdCTypesAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/LocalCCIdAst.hpp"
#include "obj/RemoteCCIdAst.hpp"
#include "obj/UnknownCCIdCTypeAst.hpp"

#include <boost/variant.hpp>

namespace lmp
{
  namespace obj
  {
    namespace ccid
    {
      namespace ast
      {
         typedef boost::variant<lmp::obj::ccid::ast::LocalCCId,
                                lmp::obj::ccid::ast::RemoteCCId,
                                lmp::obj::ccid::ast::UnknownCCIdCType>   ControlChannelIdCTypes;
         std::ostream& operator<<(
           std::ostream&        os,
           const ControlChannelIdCTypes&  ccIdCType);
      }
    }
    namespace ast
    {
      template <>
      lmp::DWORD getBodyLength<ccid::ast::ControlChannelIdCTypes>(
        const ccid::ast::ControlChannelIdCTypes&  ccIdCType);
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_CC_ID_CTYPES_HPP_ */
