#ifndef COAP_RFC3986PathAbsolute_AST_ADAPTED_HPP_
#define COAP_RFC3986PathAbsolute_AST_ADAPTED_HPP_
/*
 * RFC3986PathAbsoluteAstAdapted.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986PathAbsoluteAst.hpp"
#include <boost/fusion/include/adapt_struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(
   rfc3986::ast::PathAbsolute,
  (rfc3986::ast::SeqOfStrings,    m_pathAbsolute)
)


#endif /* COAP_RFC3986PathAbsolute_AST_ADAPTED_HPP_ */

