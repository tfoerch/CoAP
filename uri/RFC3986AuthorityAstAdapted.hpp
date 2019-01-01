#ifndef COAP_RFC3986Authority_AST_ADAPTED_HPP_
#define COAP_RFC3986Authority_AST_ADAPTED_HPP_
/*
 * RFC3986AuthorityAstAdapted.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986AuthorityAst.hpp"
#include <boost/fusion/include/adapt_struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(
   rfc3986::ast::Authority,
  (rfc3986::ast::OptString,    m_userInfo)
  (rfc3986::ast::Host,         m_host)
  (rfc3986::ast::OptUShort,    m_port)
)


#endif /* COAP_RFC3986Authority_AST_ADAPTED_HPP_ */

