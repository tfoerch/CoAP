#ifndef COAP_RFC3986PathRootLess_AST_ADAPTED_HPP_
#define COAP_RFC3986PathRootLess_AST_ADAPTED_HPP_
/*
 * RFC3986PathRootLessAstAdapted.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986PathRootLessAst.hpp"
#include <boost/fusion/include/adapt_struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(
   rfc3986::ast::PathRootLess,
  (rfc3986::ast::SeqOfStrings,    m_pathRootLess)
)


#endif /* COAP_RFC3986PathRootLess_AST_ADAPTED_HPP_ */

