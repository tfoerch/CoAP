/*
 * Scanner.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "Scanner_def.hpp"

namespace lex = boost::spirit::lex;

//typedef std::string::iterator base_iterator_type;
typedef std::string::const_iterator base_iterator_type;
typedef boost::mpl::vector<std::string> token_value_types;
// typedef lex::lexertl::token<base_iterator_type, token_value_types, boost::mpl::true_, xml::token_ids::type> token_type;
typedef lex::lexertl::token<base_iterator_type, token_value_types, boost::mpl::true_> token_type;
// typedef lex::lexertl::position_token<base_iterator_type, token_value_types, boost::mpl::true_> token_type;
typedef xml::lexer::xml_tokens<lex::lexertl::actor_lexer<token_type>>::lexer_type lexer_type;
template xml::lexer::xml_tokens<lexer_type>::xml_tokens();
//template bool xml::lexer::xml_tokens<base_iterator_type>::add_(
//    std::string const&, int);
