#ifndef LMP_OBJ_NODE_ID_CTYPES_HPP_
#define LMP_OBJ_NODE_ID_CTYPES_HPP_
/*
 * NodeIdCTypesAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/LocalNodeIdAst.hpp"
#include "obj/RemoteNodeIdAst.hpp"
#include "obj/UnknownNodeIdCTypeAst.hpp"

#include <boost/variant.hpp>

namespace lmp
{
  namespace obj
  {
    namespace nodeid
    {
      namespace ast
      {
         typedef boost::variant<lmp::obj::nodeid::ast::LocalNodeId,
                                lmp::obj::nodeid::ast::RemoteNodeId,
                                lmp::obj::nodeid::ast::UnknownNodeIdCType>   NodeIdCTypes;
         std::ostream& operator<<(
           std::ostream&        os,
           const NodeIdCTypes&  nodeIdCType);
      }
    }
    namespace ast
    {
      template <>
      lmp::DWORD getBodyLength<nodeid::ast::NodeIdCTypes>(
        const nodeid::ast::NodeIdCTypes&  nodeIdCType);
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_NODE_ID_CTYPES_HPP_ */
