#ifndef COAP_XML_AST_HPP_
#define COAP_XML_AST_HPP_
/*
 * Ast.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "TokenIds.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/spirit/include/support_extended_variant.hpp>
#include <boost/spirit/include/support_attributes.hpp>
#include <boost/optional.hpp>

#include <vector>
#include <iostream>


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

    struct Element;

    struct CharData
    {
      std::string  text;
    };

    struct Comment
    {
      std::string  text;
    };

    typedef
      boost::variant<
        boost::recursive_wrapper<Element>,
        CharData,
        Comment>
    ContentEntity;

    typedef std::vector<ContentEntity>  Content;

    struct Element
    {
      std::string  name;             // tag name
      Content      children;         // children
    };

    std::ostream& operator<<(
      std::ostream&       os,
      const CharData&     charData)
    {
      os << "CharData("<< charData.text << ")";
      return os;
    }
    std::ostream& operator<<(
      std::ostream&       os,
      const Comment&      comment)
    {
      os << "Comment("<< comment.text << ")";
      return os;
    }
    std::ostream& operator<<(
      std::ostream&         os,
      const ContentEntity&  entity)
    {
      os << "ContentEntity(" << ")";
      return os;
    }
    std::ostream& operator<<(
      std::ostream&   os,
      const Content&  entity)
    {
      for (Content::const_iterator iter = entity.begin();
          iter != entity.end();
          ++iter)
      {
        if (iter != entity.begin())
        {
          os << ", ";
        }
        os << *iter;
      }
      return os;
    }
    std::ostream& operator<<(
      std::ostream&       os,
      const Element&      element)
    {
      os << "Element("<< element.name << ": " << element.children << ")";
      return os;
    }
  }
}

BOOST_FUSION_ADAPT_STRUCT(
    xml::ast::Element,
    (std::string,        name)
    (xml::ast::Content,  children)
)

BOOST_FUSION_ADAPT_STRUCT(
    xml::ast::CharData,
    (std::string,        text)
)

BOOST_FUSION_ADAPT_STRUCT(
    xml::ast::Comment,
    (std::string,        text)
)

#endif /* COAP_XML_AST_HPP_ */

