#ifndef LMP_OBJ_LOCAL_NODE_ID_AST_HPP_
#define LMP_OBJ_LOCAL_NODE_ID_AST_HPP_
/*
 * LocalNodeIdAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectHeaderAst.hpp"
#include "obj/ObjectClassAst.hpp"
#include "obj/NodeIdClassAst.hpp"

#ifdef USE_SPIRIT_X3_PARSER
#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#endif /* USE_SPIRIT_X3_PARSER */


namespace lmp
{
  namespace obj
  {
    template <>
    struct HeaderCTypeTraits<nodeid::ClassType, nodeid::ClassType::LocalNodeId>
    {
      typedef typename nodeid::ClassType                ctype_type;
      static const ObjectClass                          obj_class;
      static const ctype_type                           ctype;
      static const lmp::WORD                            length;
    };
    namespace nodeid
    {
      namespace ast
      {
#ifdef USE_SPIRIT_X3_PARSER
        namespace x3 = boost::spirit::x3;
#endif /* USE_SPIRIT_X3_PARSER */
        struct LocalNodeId
#ifdef USE_SPIRIT_X3_PARSER
            : x3::position_tagged
#endif /* USE_SPIRIT_X3_PARSER */
        {
          typedef
            lmp::obj::ast::ObjectHeader<HeaderCTypeTraits<nodeid::ClassType,
                                                          nodeid::ClassType::LocalNodeId>>  LocalNodeIdHeaderType;

          LocalNodeIdHeaderType  m_header;
          lmp::DWORD             m_nodeId;
        };
      }
    }
    namespace ast
    {
      template <>
      lmp::DWORD getBodyLength<nodeid::ast::LocalNodeId>(
        const nodeid::ast::LocalNodeId&  objCType);
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_LOCAL_NODE_ID_AST_HPP_ */
