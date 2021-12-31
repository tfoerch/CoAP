#ifndef COAP_RFC3986IPLiteral_AST_HPP_
#define COAP_RFC3986IPLiteral_AST_HPP_
/*
 * RFC3986IPLiteralAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <array>
#include <variant>
#include <string>

namespace rfc3986
{
  namespace ast
  {
    typedef std::array<unsigned char, 16>            byte_array16;
    typedef std::variant<byte_array16, std::string>  IPLiteral;
  } // namespace ast
} // namespace rfc3986


#endif /* COAP_RFC3986IPLiteral_AST_HPP_ */

