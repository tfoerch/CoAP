#ifndef COAP_XML_SCANNER_HPP_
#define COAP_XML_SCANNER_HPP_
/*
 * Scanner.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "TokenIds.hpp"

#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/include/lex_lexertl_position_token.hpp>
#include <boost/assert.hpp>

namespace xml
{
  namespace lexer
  {
    namespace lex = boost::spirit::lex;

    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
      namespace lex = boost::spirit::lex;

      template <typename BaseIterator>
      struct get_lexer_type
      {
        // Our token needs to be able to carry several token values:
        // std::string and unsigned int
        typedef boost::mpl::vector<std::string>
          token_value_types;

        // Using the position_token class as the token type to be returned
        // from the lexer iterators allows to retain positional information
        // as every token instance stores an iterator pair pointing to the
        // matched input sequence.
        typedef lex::lexertl::position_token<
            BaseIterator, token_value_types, boost::mpl::true_
            > token_type;

        // use the lexer based on runtime generated DFA tables
        typedef lex::lexertl::actor_lexer<token_type> type;
      };
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename BaseIterator>
    struct xml_tokens
      : lex::lexer<typename detail::get_lexer_type<BaseIterator>::type>
    {
    private:
      // get the type of any qi::raw_token(...) and qi::token(...) constructs
        typedef typename boost::spirit::result_of::terminal<
            boost::spirit::tag::raw_token(token_ids::type)
        >::type raw_token_spec;

        typedef typename boost::spirit::result_of::terminal<
            boost::spirit::tag::token(token_ids::type)
        >::type token_spec;

//        typedef std::map<std::string, token_ids::type> keyword_map_type;
//
//    protected:
//        // add a keyword to the mapping table
//        bool add_(std::string const& keyword, int id = token_ids::invalid);
//
//        struct keyword_adder
//        {
//          xml_tokens& l;
//          keyword_adder(xml_tokens& l) : l(l) {}
//          keyword_adder& operator()(
//            std::string const& keyword, int id = token_ids::invalid)
//          {
//            l.add_(keyword, id);
//            return *this;
//          }
//        };
//
//        friend struct keyword_adder;
//        keyword_adder add;
//
    public:
        typedef BaseIterator base_iterator_type;

        xml_tokens();

//        // extract a raw_token(id) for the given registered keyword
//        raw_token_spec operator()(std::string const& kwd) const
//        {
//          namespace qi = boost::spirit::qi;
//          qi::raw_token_type raw_token;
//
//          typename keyword_map_type::const_iterator it = keywords_.find(kwd);
//          BOOST_ASSERT(it != keywords_.end());
//          return raw_token((it != keywords_.end()) ? (*it).second : token_ids::invalid);
//        }
//
//        // extract a token(id) for the given registered keyword
//        token_spec token(std::string const& kwd) const
//        {
//          namespace qi = boost::spirit::qi;
//          qi::token_type token;
//
//          typename keyword_map_type::const_iterator it = keywords_.find(kwd);
//          BOOST_ASSERT(it != keywords_.end());
//          return token((it != keywords_.end()) ? (*it).second : token_ids::invalid);
//        }

        lex::token_def<lex::omit>   m_etag_begin;
        lex::token_def<lex::omit>   m_tag_begin;
        lex::token_def<lex::omit>   m_emptyElem_tag_end;
        lex::token_def<lex::omit>   m_tag_end;
        lex::token_def<lex::omit>   m_etag_mark;
        lex::token_def<lex::omit>   m_declaration_mark;
        lex::token_def<lex::omit>   m_xml_decl_begin;
        lex::token_def<lex::omit>   m_xml_decl_end;
        lex::token_def<lex::omit>   m_single_quota;
        lex::token_def<lex::omit>   m_double_quote;
        lex::token_def<lex::omit>   m_equal;
        lex::token_def<lex::omit>   m_doctypedecl_begin_mark;
        lex::token_def<lex::omit>   m_cdata_begin_mark;
        lex::token_def<lex::omit>   m_cdata_end_mark;
        lex::token_def<lex::omit>   m_comment_begin_mark;
        lex::token_def<lex::omit>   m_comment_end_mark;
        lex::token_def<std::string> m_name;
        lex::token_def<std::string> m_char_data;
        lex::token_def<std::string> m_cdata;
        lex::token_def<std::string> m_whitespace;
        lex::token_def<std::string> m_comment;
//        keyword_map_type keywords_;
    };
  }
}

#endif /* COAP_XML_SCANNER_HPP_ */


