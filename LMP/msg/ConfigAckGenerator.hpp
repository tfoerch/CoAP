#ifndef LMP_MSG_CONFIGACK_GENERATOR_HPP_
#define LMP_MSG_CONFIGACK_GENERATOR_HPP_
/*
 * ConfigAckGenerator.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "MessageType.hpp"
#include "ConfigAckAst.hpp"
#include "msg/CommonHeaderGenerator.hpp"
#include "obj/LocalCCIdGenerator.hpp"
#include "obj/LocalNodeIdGenerator.hpp"
#include "obj/RemoteCCIdGenerator.hpp"
#include "obj/MessageIdAckGenerator.hpp"
#include "obj/RemoteNodeIdGenerator.hpp"
#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace msg
  {
    namespace generator
    {
      namespace karma = boost::spirit::karma;
      template <typename OutputIterator>
      struct config_ack_msg_grammar : karma::grammar<OutputIterator, ast::ConfigAck()>
      {
        config_ack_msg_grammar();

        boost::phoenix::function<lmp::msg::ast::GetLength<ast::ConfigAck>>              phx_msgLength;
        lmp::msg::generator::common_header_grammar<OutputIterator, MsgType::ConfigAck>  common_header;
        lmp::obj::generator::local_cc_id_grammar<OutputIterator>                        local_ccid;
        lmp::obj::generator::remote_cc_id_grammar<OutputIterator>                       remote_ccid;
        lmp::obj::generator::local_node_id_grammar<OutputIterator>                      local_node_id;
        lmp::obj::generator::remote_node_id_grammar<OutputIterator>                     remote_node_id;
        lmp::obj::generator::message_id_ack_grammar<OutputIterator>                     message_id_ack;

        karma::rule<OutputIterator, ast::ConfigAck()>                                    config_ack_msg_rule;
      };
    }
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_CONFIGACK_GENERATOR_HPP_ */
