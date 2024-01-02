#ifndef LMP_OBJ_REMOTE_CC_ID_AST_HPP_
#define LMP_OBJ_REMOTE_CC_ID_AST_HPP_
/*
 * RemoteCCIdAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectHeaderAst.hpp"
#include "obj/ObjectClassAst.hpp"
#include "obj/ControlChannelIdClassAst.hpp"
#ifdef USE_SPIRIT_X3_PARSER
#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#endif /* USE_SPIRIT_X3_PARSER */

namespace lmp
{
  namespace obj
  {
    template <>
    struct HeaderCTypeTraits<ccid::ClassType, ccid::ClassType::RemoteCCId>
    {
      typedef typename ccid::ClassType                  ctype_type;
      static const ObjectClass                          obj_class;
      static const ctype_type                           ctype;
      static const lmp::WORD                            length;
   };
    namespace ccid
    {
      namespace ast
      {
#ifdef USE_SPIRIT_X3_PARSER
        namespace x3 = boost::spirit::x3;
#endif /* USE_SPIRIT_X3_PARSER */
        struct RemoteCCId
#ifdef USE_SPIRIT_X3_PARSER
            : x3::position_tagged
#endif /* USE_SPIRIT_X3_PARSER */
        {
          typedef
            lmp::obj::ast::ObjectHeader<HeaderCTypeTraits<ccid::ClassType,
                                                          ccid::ClassType::RemoteCCId>>  RemoteCCIdHeaderType;

          RemoteCCIdHeaderType  m_header;
          lmp::DWORD            m_ccId;
        };
      }
    }
    namespace ast
    {
      template <>
      lmp::DWORD getBodyLength<ccid::ast::RemoteCCId>(
        const ccid::ast::RemoteCCId&  objCType);
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_REMOTE_CC_ID_AST_HPP_ */
