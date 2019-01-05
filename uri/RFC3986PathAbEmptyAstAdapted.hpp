#ifndef COAP_RFC3986PathAbEmpty_AST_ADAPTED_HPP_
#define COAP_RFC3986PathAbEmpty_AST_ADAPTED_HPP_
/*
 * RFC3986PathAbEmptyAstAdapted.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986PathAbEmptyAst.hpp"
#include <boost/fusion/include/adapt_struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(
   rfc3986::ast::PathAbEmpty,
  (rfc3986::ast::SeqOfStrings,    m_pathAbEmpty)
)


#endif /* COAP_RFC3986PathAbEmpty_AST_ADAPTED_HPP_ */

