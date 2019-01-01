#ifndef COAP_RFC3986Host_AST_HPP_
#define COAP_RFC3986Host_AST_HPP_
/*
 * RFC3986HostAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986IPLiteralAst.hpp"
#include <boost/cstdint.hpp>
#include <boost/asio/detail/array.hpp>
#include <boost/variant.hpp>
#include <string>

namespace rfc3986
{
  namespace ast
  {
    typedef boost::asio::detail::array<unsigned char, 4> byte_array4;
    typedef boost::variant<IPLiteral, byte_array4, std::string>  Host;
  } // namespace ast
} // namespace rfc3986


#endif /* COAP_RFC3986Host_AST_HPP_ */

