#ifndef LMP_OBJ_LOCAL_NODE_ID_GENERATOR_HPP_
#define LMP_OBJ_LOCAL_NODE_ID_GENERATOR_HPP_
/*
 * LocalNodeIdGenerator.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/LocalNodeIdAst.hpp"
#include "obj/ObjectHeaderGenerator.hpp"

#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace obj
  {
//    lmp::DWORD getLength(
//      const nodeid::ast::LocalNodeId&  localNodeId);
//    struct GetLengthLocalNodeId
//    {
//      template<typename> struct result { typedef lmp::WORD type; };
//      lmp::WORD operator()(
//        const nodeid::ast::LocalNodeId& localNodeId) const
//      {
//        return getLength(localNodeId);
//      }
//    };
    namespace generator
    {
      namespace karma = boost::spirit::karma;
      template <typename OutputIterator>
      struct local_node_id_grammar : karma::grammar<OutputIterator, nodeid::ast::LocalNodeId()>
      {
        local_node_id_grammar();

        boost::phoenix::function<ast::GetLength<nodeid::ast::LocalNodeId>>   phx_getLength;
        lmp::obj::generator::object_header_grammar<OutputIterator, nodeid::ClassType, nodeid::ClassType::LocalNodeId> object_header;
        karma::rule<OutputIterator, nodeid::ast::LocalNodeId()>  local_node_id_rule;
      };
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_LOCAL_NODE_ID_GENERATOR_HPP_ */
