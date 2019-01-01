#ifndef COAP_RFC3986Authority_AST_HPP_
#define COAP_RFC3986Authority_AST_HPP_
/*
 * RFC3986AuthorityAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "uri/RFC3986HostAst.hpp"
#include <boost/cstdint.hpp>
#include <boost/asio/detail/array.hpp>
#include <boost/optional.hpp>
#include <string>

namespace rfc3986
{
  namespace ast
  {
    typedef boost::optional<std::string>      OptString;
    typedef boost::optional<boost::uint16_t>  OptUShort;
    struct Authority
    {
      OptString  m_userInfo;
      Host       m_host;
      OptUShort  m_port;
    };
  } // namespace ast
} // namespace rfc3986


#endif /* COAP_RFC3986Authority_AST_HPP_ */

