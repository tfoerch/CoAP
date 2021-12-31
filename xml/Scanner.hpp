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
#include <boost/spirit/include/lex_lexertl_token.hpp>
//#include <boost/spirit/include/lex_lexertl_position_token.hpp>
#include <boost/assert.hpp>

namespace xml
{
  namespace lexer
  {
    namespace lex = boost::spirit::lex;

    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
      struct set_lexer_state
      {
        set_lexer_state(char const* state_)
        : state(state_) {}

        // This is called by the semantic action handling code during the lexing
        template <typename Iterator, typename Context>
        void operator()(
          Iterator const&,
          Iterator const&,
          BOOST_SCOPED_ENUM(boost::spirit::lex::pass_flags)&,
          std::size_t&, Context& ctx) const
        {
          ctx.set_state_name(state.c_str());
        }

        std::string state;
      };
#if 0
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
#endif
    }
    ///////////////////////////////////////////////////////////////////////////
    template <typename Lexer>
    struct xml_tokens : lex::lexer<Lexer>
    {
    private:
      // get the type of any qi::raw_token(...) and qi::token(...) constructs
//        typedef typename boost::spirit::result_of::terminal<
//            boost::spirit::tag::raw_token(token_ids::type)
//        >::type raw_token_spec;
//
//        typedef typename boost::spirit::result_of::terminal<
//            boost::spirit::tag::token(token_ids::type)
//        >::type token_spec;
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
//        typedef BaseIterator base_iterator_type;
//      using PlainTokenIdType = lex::token_def<lex::omit, char, token_ids::type>;
//      using TextTokenIdType = lex::token_def<std::string, char, token_ids::type>;
      using PlainTokenIdType = lex::token_def<lex::omit, char>;
      using TextTokenIdType = lex::token_def<std::string, char>;

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

        PlainTokenIdType   m_etag_begin;
        PlainTokenIdType   m_tag_begin;
//        PlainTokenIdType   m_emptyElem_tag_end;
//        PlainTokenIdType   m_tag_end;
//        PlainTokenIdType   m_etag_mark;
//        PlainTokenIdType   m_declaration_mark;
        PlainTokenIdType   m_etag_begin_TAG;
        PlainTokenIdType   m_tag_begin_TAG;
        PlainTokenIdType   m_emptyElem_tag_end_TAG;
        PlainTokenIdType   m_tag_end_TAG;
        PlainTokenIdType   m_etag_mark_TAG;
        PlainTokenIdType   m_declaration_mark_TAG;
//        PlainTokenIdType   m_xml_decl_begin;
//        PlainTokenIdType   m_xml_decl_end;
//        PlainTokenIdType   m_single_quota;
//        PlainTokenIdType   m_double_quote;
//        PlainTokenIdType   m_equal;
//        PlainTokenIdType   m_doctypedecl_begin_mark;
//        PlainTokenIdType   m_cdata_begin_mark;
//        PlainTokenIdType   m_cdata_end_mark;
//        PlainTokenIdType   m_comment_begin_mark;
//        PlainTokenIdType   m_comment_end_mark;
        // PlainTokenIdType   m_question_mark;
        // PlainTokenIdType   m_two dashes;
        TextTokenIdType m_name;
        TextTokenIdType m_char_data;
//        TextTokenIdType m_cdata;
//        TextTokenIdType m_whitespace;
//        TextTokenIdType m_comment;
//        keyword_map_type keywords_;
    };
  }
}

#endif /* COAP_XML_SCANNER_HPP_ */
