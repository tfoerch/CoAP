#ifndef LMP_MSG_HELLO_AST_ADAPTED_HPP_
#define LMP_MSG_HELLO_AST_ADAPTED_HPP_
/*
 * HelloAstAdapted.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "HelloAst.hpp"
#include <boost/fusion/include/adapt_struct.hpp>


BOOST_FUSION_ADAPT_STRUCT(
  lmp::msg::ast::Hello,
  (lmp::msg::ast::CommonHeaderFlags,    m_header)
  (lmp::obj::hello::ast::Hello,         m_hello)
)

#endif /* LMP_MSG_HELLO_AST_ADAPTED_HPP_ */
