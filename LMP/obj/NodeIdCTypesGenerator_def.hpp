#ifndef LMP_OBJ_NODE_ID_CTYPES_GENERATOR_DEF_HPP_
#define LMP_OBJ_NODE_ID_CTYPES_DEF_GENERATOR_HPP_
/*
 * NodeIdCTypesGenerator_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/NodeIdCTypesGenerator.hpp"
#include "obj/LocalNodeIdGenerator_def.hpp"
#include "obj/RemoteNodeIdGenerator_def.hpp"
#include "obj/ObjectClassUnknownCTypeGenerator_def.hpp"
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/object/static_cast.hpp>

namespace lmp
{
  namespace obj
  {
    namespace nodeid
    {
      namespace generator
      {
        namespace fusion = boost::fusion;
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;

        template <typename OutputIterator>
        node_id_ctypes_grammar<OutputIterator>::node_id_ctypes_grammar()
        : node_id_ctypes_grammar::base_type(node_id_ctypes_rule, "node_id_ctypes")
        {
          using phoenix::at_c;
          using namespace qi::labels;

          node_id_ctypes_rule %=
              local_nodeid |
              remote_nodeid |
              unknown_nodeid_ctype
              ;

          node_id_ctypes_rule.name("node_id_ctypes");
        }
      } // namespace generate
    } // namespace nodeid
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_NODE_ID_CTYPES_GENERATOR_DEF_HPP_ */
