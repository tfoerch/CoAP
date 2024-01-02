#ifndef LMP_OBJ_NODE_ID_CTYPES_PARSER_DEF_HPP_
#define LMP_OBJ_NODE_ID_CTYPES_PARSER_DEF_HPP_
/*
 * NodeIdCTypesParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/NodeIdCTypesParser.hpp"
#include "obj/LocalNodeIdParser_def.hpp"
#include "obj/RemoteNodeIdParser_def.hpp"
#ifdef USE_SPIRIT_X3_PARSER
#include "obj/UnknownNodeIdCTypeParser_def.hpp"
#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>
#include <boost/spirit/home/x3.hpp>
#else
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/object/static_cast.hpp>
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
        namespace fusion = boost::fusion;

        ///////////////////////////////////////////////////////////////////////////
        // Rules
        ///////////////////////////////////////////////////////////////////////////

        node_id_ctypes_type const node_id_ctypes = "node_id_ctypes";


        ///////////////////////////////////////////////////////////////////////////
        // Grammar
        ///////////////////////////////////////////////////////////////////////////

        auto const node_id_ctypes_def =
          local_node_id |
          remote_node_id |
          unknown_node_id_ctype
          ;

        BOOST_SPIRIT_DEFINE(node_id_ctypes);

        ///////////////////////////////////////////////////////////////////////////
        // Annotation and Error handling
        ///////////////////////////////////////////////////////////////////////////

        // We want error-handling only for the start (outermost) rexpr
        // rexpr is the same as rexpr_inner but without error-handling (see error_handler.hpp)
        struct node_id_ctypes_class : x3::annotate_on_success/*, error_handler_base*/ {};
#else
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;

        template <typename Iterator>
        node_id_ctypes_grammar<Iterator>::node_id_ctypes_grammar()
        : node_id_ctypes_grammar::base_type(node_id_ctypes_rule,
                                                       "node_id_ctypes")
        {
          using qi::big_word;
          using qi::big_dword;
          using qi::_1;
          using phoenix::at_c;
          using namespace qi::labels;

          node_id_ctypes_rule %=
              local_nodeid |
              remote_nodeid |
              unknown_nodeid_ctype
              ;

          node_id_ctypes_rule.name("node_id_ctypes");
        }
#endif /* USE_SPIRIT_X3_PARSER */
      } // namespace parser

#ifdef USE_SPIRIT_X3_PARSER
      parser::node_id_ctypes_type const& node_id_ctypes()
      {
        return parser::node_id_ctypes;
      }
#endif /* USE_SPIRIT_X3_PARSER */
    } // namespace nodeid
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_NODE_ID_CTYPES_PARSER_DEF_HPP_ */
