#ifndef COAP_RFC3986Uri_AST_ADAPTED_HPP_
#define COAP_RFC3986Uri_AST_ADAPTED_HPP_
/*
 * RFC3986UriAstAdapted.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986UriAst.hpp"
#include <boost/fusion/include/adapt_struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(
   rfc3986::ast::Uri,
  (std::string,              m_scheme)
  (rfc3986::ast::HierPart,   m_hier_part)
  (rfc3986::ast::OptString,  m_query)
  (rfc3986::ast::OptString,  m_fragment)
)


#endif /* COAP_RFC3986Uri_AST_ADAPTED_HPP_ */

