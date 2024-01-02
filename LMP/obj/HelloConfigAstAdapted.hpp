#ifndef LMP_OBJ_HELLO_CONFIG_AST_ADAPTED_HPP_
#define LMP_OBJ_HELLO_CONFIG_AST_ADAPTED_HPP_
/*
 * HelloConfigAstAdapted.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/HelloConfigAst.hpp"
#include <boost/fusion/include/adapt_struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(
  lmp::obj::config::ast::HelloConfig,
  (lmp::obj::config::ast::HelloConfig::HelloConfigHeaderType,  m_header)
  (lmp::WORD,                                                  m_helloIntv)
  (lmp::WORD,                                                  m_helloDeadIntv)
)

#endif /* LMP_OBJ_HELLO_CONFIG_AST_ADAPTED_HPP_ */
