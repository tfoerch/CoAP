/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2001-2011 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include "Scanner.hpp"
#include "Parser_def.hpp"

namespace lex = boost::spirit::lex;

//typedef std::string::iterator base_iterator_type;
 typedef std::string::const_iterator base_iterator_type;
typedef boost::mpl::vector<std::string> token_value_types;
typedef lex::lexertl::token<base_iterator_type, token_value_types, boost::mpl::true_> token_type;
// typedef lex::lexertl::token<base_iterator_type, token_value_types, boost::mpl::true_, xml::token_ids::type> token_type;
// typedef lex::lexertl::position_token<base_iterator_type, token_value_types, boost::mpl::true_> token_type;
typedef xml::lexer::xml_tokens<lex::lexertl::actor_lexer<token_type>> xml_lexer_type;
typedef xml_lexer_type::lexer_type lexer_type;
typedef lexer_type::iterator_type iterator_type;

template struct xml::parser::element<iterator_type>;
template xml::parser::element<iterator_type>::element(const xml_lexer_type&);

