#ifndef LMP_OBJ_MESSAGE_ID_ACK_AST_ADAPTED_HPP_
#define LMP_OBJ_MESSAGE_ID_ACK_AST_ADAPTED_HPP_
/*
 * MessageIdAckAstAdapted.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/MessageIdAckAst.hpp"
#include <boost/fusion/include/adapt_struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(
  lmp::obj::msgid::ast::MessageIdAck,
  (lmp::obj::msgid::ast::MessageIdAck::MessageIdAckHeaderType,  m_header)
  (lmp::DWORD,                                                  m_msgId)
)

#endif /* LMP_OBJ_MESSAGE_ID_ACK_AST_ADAPTED_HPP_ */
