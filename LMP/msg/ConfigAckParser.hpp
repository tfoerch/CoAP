#ifndef LMP_MSG_CONFIGACK_PARSER_HPP_
#define LMP_MSG_CONFIGACK_PARSER_HPP_
/*
 * ConfigAckParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "ConfigAckAst.hpp"
#include "msg/CommonHeaderParser.hpp"
#include "obj/LocalCCIdParser.hpp"
#include "obj/LocalNodeIdParser.hpp"
#include "obj/RemoteCCIdParser.hpp"
#include "obj/MessageIdAckParser.hpp"
#include "obj/RemoteNodeIdParser.hpp"
#include <boost/spirit/include/qi.hpp>

namespace lmp
{
  namespace msg
  {
    namespace parser
    {
      namespace qi = boost::spirit::qi;
      template <typename Iterator>
      struct config_ack_msg_grammar : qi::grammar<Iterator,
                                                  ast::ConfigAck(ast::CommonHeaderFlags),
                                                  qi::locals<lmp::WORD>>
      {
        config_ack_msg_grammar();

        lmp::msg::parser::common_header_length_grammar<Iterator>  common_header_length;
        lmp::obj::parser::local_cc_id_grammar<Iterator>           local_ccid;
        lmp::obj::parser::remote_cc_id_grammar<Iterator>          remote_ccid;
        lmp::obj::parser::local_node_id_grammar<Iterator>         local_node_id;
        lmp::obj::parser::remote_node_id_grammar<Iterator>        remote_node_id;
        lmp::obj::parser::message_id_ack_grammar<Iterator>        message_id_ack;
        qi::rule<Iterator,
                 ast::ConfigAck(ast::CommonHeaderFlags),
                 qi::locals<lmp::WORD>>                           config_ack_msg_rule;
      };
    }
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_CONFIGACK_PARSER_HPP_ */
