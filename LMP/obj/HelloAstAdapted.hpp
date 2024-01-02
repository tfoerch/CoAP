#ifndef LMP_OBJ_HELLO_AST_ADAPTED_HPP_
#define LMP_OBJ_HELLO_AST_ADAPTED_HPP_
/*
 * HelloAstAdapted.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/HelloAst.hpp"
#include <boost/fusion/include/adapt_struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(
  lmp::obj::hello::ast::Hello,
  (lmp::obj::hello::ast::Hello::HelloHeaderType,  m_header)
  (lmp::DWORD,                                    m_txSeqNum)
  (lmp::DWORD,                                    m_rcvSeqNum)
)

#endif /* LMP_OBJ_HELLO_AST_ADAPTED_HPP_ */
