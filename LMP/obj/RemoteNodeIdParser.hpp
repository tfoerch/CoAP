#ifndef LMP_OBJ_REMOTE_NODE_ID_PARSER_HPP_
#define LMP_OBJ_REMOTE_NODE_ID_PARSER_HPP_
/*
 * RemoteNodeIdParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/RemoteNodeIdAst.hpp"

#ifdef USE_SPIRIT_X3_PARSER
#include <boost/spirit/home/x3/support/traits/is_variant.hpp>
#include <boost/spirit/home/x3/support/traits/tuple_traits.hpp>
#include <boost/spirit/home/x3/nonterminal/rule.hpp>
#else
#include "obj/ObjectHeaderParser.hpp"
#include <boost/spirit/include/qi.hpp>
#endif /* USE_SPIRIT_X3_PARSER */

namespace lmp
{
  namespace obj
  {
    namespace parser
    {
#ifdef USE_SPIRIT_X3_PARSER
      namespace x3 = boost::spirit::x3;

      struct remote_node_id_class;
      typedef
        x3::rule<remote_node_id_class, nodeid::ast::RemoteNodeId>  remote_node_id_type;
      BOOST_SPIRIT_DECLARE(remote_node_id_type);
#else
      namespace qi = boost::spirit::qi;
      template <typename Iterator>
      struct remote_node_id_grammar : qi::grammar<Iterator, nodeid::ast::RemoteNodeId()>
      {
        remote_node_id_grammar();
        lmp::obj::parser::object_header_fix_length_grammar<Iterator,
                                                           nodeid::ClassType,
                                                           nodeid::ClassType::RemoteNodeId>  object_header;
        qi::rule<Iterator, nodeid::ast::RemoteNodeId()>                                      remote_node_id_rule;
      };

#endif /* USE_SPIRIT_X3_PARSER */
    }
#ifdef USE_SPIRIT_X3_PARSER
    parser::remote_node_id_type const& remote_node_id();
#endif /* USE_SPIRIT_X3_PARSER */
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_REMOTE_NODE_ID_PARSER_HPP_ */
