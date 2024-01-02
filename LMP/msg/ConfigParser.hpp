#ifndef LMP_MSG_CONFIG_PARSER_HPP_
#define LMP_MSG_CONFIG_PARSER_HPP_
/*
 * ConfigParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "ConfigAst.hpp"
#include "msg/CommonHeaderParser.hpp"
#include "obj/LocalCCIdParser.hpp"
#include "obj/MessageIdParser.hpp"
#include "obj/LocalNodeIdParser.hpp"
#include "obj/ConfigObjectSequenceParser.hpp"
#include <boost/spirit/include/qi.hpp>

namespace lmp
{
  namespace msg
  {
    namespace parser
    {
      namespace qi = boost::spirit::qi;
      namespace phoenix = boost::phoenix;
      template <typename Iterator>
      struct config_msg_grammar : qi::grammar<Iterator,
                                              ast::Config(ast::CommonHeaderFlags),
                                              qi::locals<lmp::WORD>>
      {
        config_msg_grammar();

        boost::phoenix::function<lmp::obj::ast::GetLength<obj::ccid::ast::LocalCCId>>      phx_getCCIdLength;
        boost::phoenix::function<lmp::obj::ast::GetLength<obj::nodeid::ast::LocalNodeId>>  phx_getNodeIdLength;
        boost::phoenix::function<lmp::obj::ast::GetLength<obj::msgid::ast::MessageId>>     phx_getMessageIdLength;
        lmp::msg::parser::common_header_length_grammar<Iterator>                      common_header_length;
        lmp::obj::parser::local_cc_id_grammar<Iterator>                               local_ccid;
        lmp::obj::parser::local_node_id_grammar<Iterator>                             local_node_id;
        lmp::obj::parser::message_id_grammar<Iterator>                                message_id;
        lmp::obj::config::parser::config_object_sequence_grammar<Iterator>            config_object_sequence;
        qi::rule<Iterator,
                 ast::Config(ast::CommonHeaderFlags),
                 qi::locals<lmp::WORD>>                                               config_msg_rule;
      };
    }
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_CONFIG_PARSER_HPP_ */
