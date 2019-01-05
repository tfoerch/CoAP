#ifndef COAP_RFC3986HierPart_AST_ADAPTED_HPP_
#define COAP_RFC3986HierPart_AST_ADAPTED_HPP_
/*
 * RFC3986HierPartAstAdapted.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986HierPartAst.hpp"
#include <boost/fusion/include/adapt_struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(
   rfc3986::ast::AuthorityAndPathAbEmpty,
  (rfc3986::ast::Authority,    m_authority)
  (rfc3986::ast::PathAbEmpty,  m_pathAbEmpty)
)


#endif /* COAP_RFC3986HierPart_AST_ADAPTED_HPP_ */

