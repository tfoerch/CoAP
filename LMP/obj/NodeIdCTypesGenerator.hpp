#ifndef LMP_OBJ_NODE_ID_CTYPES_GENERATOR_HPP_
#define LMP_OBJ_NODE_ID_CTYPES_GENERATOR_HPP_
/*
 * NodeIdCTypesGenerator.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/LocalNodeIdGenerator.hpp"
#include "obj/RemoteNodeIdGenerator.hpp"
#include "obj/ObjectClassUnknownCTypeGenerator.hpp"
#include "obj/NodeIdCTypesAst.hpp"

#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace obj
  {
    namespace nodeid
    {
      lmp::DWORD getLength(
        const ast::NodeIdCTypes&  controlChannelIdCTypes);
      std::ostream& operator<<(
        std::ostream&                       os,
        const ast::NodeIdCTypes&  controlChannelIdCTypes);
      namespace generator
      {
        namespace karma = boost::spirit::karma;
        template <typename OutputIterator>
        struct node_id_ctypes_grammar : karma::grammar<OutputIterator, ast::NodeIdCTypes()>
        {
          node_id_ctypes_grammar();

          lmp::obj::generator::local_node_id_grammar<OutputIterator>                             local_nodeid;
          lmp::obj::generator::remote_node_id_grammar<OutputIterator>                            remote_nodeid;
          lmp::obj::generator::object_class_unknown_ctype_grammar<OutputIterator,
                                                                 lmp::obj::ObjectClass::NodeID>  unknown_nodeid_ctype;
          karma::rule<OutputIterator, ast::NodeIdCTypes()>                                       node_id_ctypes_rule;
        };
      }
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_NODE_ID_CTYPES_GENERATOR_HPP_ */
