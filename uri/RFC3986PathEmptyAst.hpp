#ifndef COAP_RFC3986PathEmpty_AST_HPP_
#define COAP_RFC3986PathEmpty_AST_HPP_
/*
 * RFC3986PathEmptyAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <string>
#include <vector>

namespace rfc3986
{
  namespace ast
  {
    typedef std::vector<std::string>  SeqOfStrings;
    struct PathEmpty
    {
      SeqOfStrings  m_pathEmpty;
    };
  } // namespace ast
} // namespace rfc3986


#endif /* COAP_RFC3986PathEmpty_AST_HPP_ */

