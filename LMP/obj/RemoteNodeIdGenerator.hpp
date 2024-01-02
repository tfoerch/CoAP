#ifndef LMP_OBJ_REMOTE_NODE_ID_GENERATOR_HPP_
#define LMP_OBJ_REMOTE_NODE_ID_GENERATOR_HPP_
/*
 * RemoteNodeIdGenerator.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/RemoteNodeIdAst.hpp"
#include "obj/ObjectHeaderGenerator.hpp"

#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace obj
  {
//    lmp::DWORD getLength(
//      const nodeid::ast::RemoteNodeId&  remoteNodeId);
//    struct GetLengthRemoteNodeId
//    {
//      template<typename> struct result { typedef lmp::WORD type; };
//      lmp::WORD operator()(
//        const nodeid::ast::RemoteNodeId& remoteNodeId) const
//      {
//        return getLength(remoteNodeId);
//      }
//    };
    namespace generator
    {
      namespace karma = boost::spirit::karma;
      template <typename OutputIterator>
      struct remote_node_id_grammar : karma::grammar<OutputIterator, nodeid::ast::RemoteNodeId()>
      {
        remote_node_id_grammar();

        boost::phoenix::function<ast::GetLength<nodeid::ast::RemoteNodeId>>   phx_getLength;
        lmp::obj::generator::object_header_grammar<OutputIterator, nodeid::ClassType, nodeid::ClassType::RemoteNodeId> object_header;
        karma::rule<OutputIterator, nodeid::ast::RemoteNodeId()>  remote_node_id_rule;
      };
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_REMOTE_NODE_ID_GENERATOR_HPP_ */
