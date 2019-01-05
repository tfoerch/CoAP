#ifndef COAP_RFC3986HierPart_AST_HPP_
#define COAP_RFC3986HierPart_AST_HPP_
/*
 * RFC3986HierPartAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986AuthorityAst.hpp"
#include "uri/RFC3986PathAbEmptyAst.hpp"
#include "uri/RFC3986PathAbsoluteAst.hpp"
#include "uri/RFC3986PathRootLessAst.hpp"
#include "uri/RFC3986PathEmptyAst.hpp"
#include <boost/variant.hpp>

namespace rfc3986
{
  namespace ast
  {
    struct AuthorityAndPathAbEmpty
    {
      Authority     m_authority;
      PathAbEmpty   m_pathAbEmpty;
    };
    typedef
      boost::variant<AuthorityAndPathAbEmpty,
                     PathAbsolute,
                     PathRootLess,
                     PathEmpty>  HierPart;
  } // namespace ast
} // namespace rfc3986


#endif /* COAP_RFC3986HierPart_AST_HPP_ */

