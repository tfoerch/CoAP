#ifndef COAP_RFC3986Uri_AST_HPP_
#define COAP_RFC3986Uri_AST_HPP_
/*
 * RFC3986UriAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986HierPartAst.hpp"
#include <optional>
#include <string>

namespace rfc3986
{
  namespace ast
  {
    typedef std::optional<std::string>      OptString;
    struct Uri
    {
      std::string  m_scheme;
      HierPart     m_hier_part;
      OptString    m_query;
      OptString    m_fragment;
    };
  } // namespace ast
} // namespace rfc3986


#endif /* COAP_RFC3986Uri_AST_HPP_ */

