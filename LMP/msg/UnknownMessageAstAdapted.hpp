#ifndef LMP_MSG_UNKNOWN_MESSAGE_AST_ADAPTED_HPP_
#define LMP_MSG_UNKNOWN_MESSAGE_AST_ADAPTED_HPP_
/*
 * UnknownMessageAstAdapted.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "UnknownMessageAst.hpp"
#include <boost/fusion/include/adapt_struct.hpp>


BOOST_FUSION_ADAPT_STRUCT(
  lmp::msg::ast::UnknownMessage,
  (lmp::msg::ast::CommonHeaderUnknownMsgType,    m_header)
  (lmp::obj::ast::ObjectSequence,                m_objects)
)


#endif /* LMP_MSG_UNKNOWN_MESSAGE_AST_ADAPTED_HPP_ */
