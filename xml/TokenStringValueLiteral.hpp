#ifndef COAP_XML_TOKEN_STRING_VALUE_LITERAL_HPP_
#define COAP_XML_TOKEN_STRING_VALUE_LITERAL_HPP_
/*
 * TokenStringValueLiteral.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>
#include <string>

namespace literal_token
{
  namespace qi = boost::spirit::qi;
  namespace lex = boost::spirit::lex;

  template <typename TokenAttr>
  struct LiteralToken : qi::primitive_parser<LiteralToken<TokenAttr>>
  {
    LiteralToken(const lex::token_def<TokenAttr> &tok, const TokenAttr &value)
    : id(tok.id()),
      value(value)
    {}

    template <typename Context, typename Iterator>
    struct attribute
    {
      typedef boost::spirit::unused_type type;
    };

    template <typename Iterator, typename Context, typename Skipper, typename Attribute>
    bool parse(Iterator& first, Iterator const& last, Context& context, Skipper const& skipper, Attribute& attr_) const
    {
      typedef typename Iterator::token_type::token_value_type token_value_type;
      typedef typename Iterator::base_iterator_type base_iterator_type;

      base_iterator_type it;

      qi::skip_over(first, last, skipper);
      if (first != last && id == first->id())
      {
        auto v = boost::get<boost::iterator_range<base_iterator_type>>(first->value());
        if (v == value)
        {
          boost::spirit::traits::assign_to(*first, attr_);
          ++first;
          return true;
        }
      }
      return false;
    }

    typename lex::token_def<TokenAttr>::id_type id;
    TokenAttr                                   value;
  };
} // literal_token

namespace boost
{
  namespace spirit
  {
    template <typename A0, typename A1>
    struct use_terminal<qi::domain,
                        terminal_ex<tag::lit,
                                    fusion::vector2<A0, A1>>,
                        typename enable_if<boost::is_same<A0, lex::token_def<std::string>>>::type> : mpl::true_
    {};

    namespace qi
    {
      template <typename Modifiers, typename A0, typename A1>
      struct make_primitive<terminal_ex<tag::lit,
                                        fusion::vector2<A0, A1> >,
                            Modifiers,
                            typename enable_if<boost::is_same<A0, lex::token_def<std::string>>>::type>
      {
        typedef literal_token::LiteralToken<std::string> result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, unused_type) const
        {
          return result_type(fusion::at_c<0>(term.args), fusion::at_c<1>(term.args));
        }
      };
    }
  }
}

#endif /* COAP_XML_TOKEN_STRING_VALUE_LITERAL_HPP_ */

