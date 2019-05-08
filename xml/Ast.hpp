#ifndef COAP_XML_AST_HPP_
#define COAP_XML_AST_HPP_
/*
 * Ast.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <boost/config/warning_disable.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/spirit/include/support_extended_variant.hpp>
#include <boost/spirit/include/support_attributes.hpp>
#include <boost/optional.hpp>
#include <vector>

#include "TokenIds.hpp"

namespace xml
{
  namespace ast
  {
  ///////////////////////////////////////////////////////////////////////////
  //  The AST
  ///////////////////////////////////////////////////////////////////////////
    struct tagged
    {
      int id; // Used to annotate the AST with the iterator position.
              // This id is used as a key to a map<int, Iterator>
              // (not really part of the AST.)
    };

    struct element;

    typedef
      boost::variant<
        boost::recursive_wrapper<element>,
        std::string>
    content;

    struct element
    {
      std::string name;                      // tag name
      std::vector<content> children;         // children
    };

  }
}


BOOST_FUSION_ADAPT_STRUCT(
    xml::ast::element,
    (std::string, name)
    (std::vector<xml::ast::content>, children)
)

#endif /* COAP_XML_AST_HPP_ */

