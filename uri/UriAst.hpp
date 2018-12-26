#ifndef COAP_URI_AST_HPP_
#define COAP_URI_AST_HPP_
/*
 * UriAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <boost/cstdint.hpp>
#include <string>

namespace coap
{
  namespace ast
  {
    enum class CoAPSchemeType : boost::uint8_t
    {
      coap = 1,
      coaps
    };
    struct UriComponents
    {
      CoAPSchemeType  m_schemeType;
    };
  } // namespace ast
} // namespace coap


#endif /* COAP_URI_AST_HPP_ */

