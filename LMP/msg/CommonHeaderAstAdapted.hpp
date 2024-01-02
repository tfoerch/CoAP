#ifndef LMP_MSG_COMMONHEADER_AST_ADAPTED_HPP_
#define LMP_MSG_COMMONHEADER_AST_ADAPTED_HPP_
/*
 * CommonHeader_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "msg/CommonHeaderAst.hpp"
#include <boost/fusion/include/adapt_struct.hpp>


BOOST_FUSION_ADAPT_STRUCT(
  lmp::msg::ast::CommonHeaderFlags,
  (bool,       m_controlChannelDown)
  (bool,       m_LMP_restart)
)

BOOST_FUSION_ADAPT_STRUCT(
  lmp::msg::ast::CommonHeaderUnknownMsgType,
  (lmp::BYTE,                         m_msgType)
  (lmp::msg::ast::CommonHeaderFlags,  m_flags)
)

#endif /* LMP_MSG_COMMONHEADER_AST_ADAPTED_HPP_ */
