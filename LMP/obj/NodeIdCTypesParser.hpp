#ifndef LMP_OBJ_NODE_ID_CTYPES_PARSER_HPP_
#define LMP_OBJ_NODE_ID_CTYPES_PARSER_HPP_
/*
 * NodeIdCTypesParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/NodeIdCTypesAst.hpp"

#ifdef USE_SPIRIT_X3_PARSER
#include <boost/spirit/home/x3/support/traits/is_variant.hpp>
#include <boost/spirit/home/x3/support/traits/tuple_traits.hpp>
#include <boost/spirit/home/x3/nonterminal/rule.hpp>
#else
#include "obj/LocalNodeIdParser.hpp"
#include "obj/RemoteNodeIdParser.hpp"
#include "obj/ObjectClassUnknownCTypeParser.hpp"
#include <boost/spirit/include/qi.hpp>
#endif /* USE_SPIRIT_X3_PARSER */

namespace lmp
{
  namespace obj
  {
    namespace nodeid
    {
      namespace parser
      {
#ifdef USE_SPIRIT_X3_PARSER
        namespace x3 = boost::spirit::x3;

        struct node_id_ctypes_class;
        typedef
          x3::rule<node_id_ctypes_class, nodeid::ast::NodeIdCTypes>  node_id_ctypes_type;
        BOOST_SPIRIT_DECLARE(node_id_ctypes_type);
#else

        namespace qi = boost::spirit::qi;
        template <typename Iterator>
        struct node_id_ctypes_grammar : qi::grammar<Iterator, nodeid::ast::NodeIdCTypes()>
        {
          node_id_ctypes_grammar();

          lmp::obj::parser::local_node_id_grammar<Iterator>                          local_nodeid;
          lmp::obj::parser::remote_node_id_grammar<Iterator>                         remote_nodeid;
          lmp::obj::parser::object_class_unknown_ctype_grammar<Iterator,
                                                               ObjectClass::NodeID>  unknown_nodeid_ctype;
          qi::rule<Iterator, nodeid::ast::NodeIdCTypes()>                            node_id_ctypes_rule;
        };
#endif /* USE_SPIRIT_X3_PARSER */
      }
#ifdef USE_SPIRIT_X3_PARSER
      parser::node_id_ctypes_type const& node_id_ctypes();
#endif /* USE_SPIRIT_X3_PARSER */
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_NODE_ID_CTYPES_PARSER_HPP_ */
