#ifndef LMP_MSG_CONFIG_GENERATOR_HPP_
#define LMP_MSG_CONFIG_GENERATOR_HPP_
/*
 * ConfigGenerator.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "ConfigAst.hpp"
#include "msg/CommonHeaderGenerator.hpp"
#include "obj/LocalCCIdGenerator.hpp"
#include "obj/MessageIdGenerator.hpp"
#include "obj/LocalNodeIdGenerator.hpp"
#include "obj/ConfigObjectSequenceGenerator.hpp"
#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace msg
  {
    namespace generator
    {
      namespace karma = boost::spirit::karma;
      template <typename OutputIterator>
      struct config_msg_grammar : karma::grammar<OutputIterator, ast::Config()>
      {
        config_msg_grammar();

        boost::phoenix::function<lmp::msg::ast::GetLength<ast::Config>>                     phx_msgLength;
        lmp::msg::generator::common_header_grammar<OutputIterator, MsgType::Config>         common_header;
        lmp::obj::generator::local_cc_id_grammar<OutputIterator>                            local_ccid;
        lmp::obj::generator::local_node_id_grammar<OutputIterator>                          local_node_id;
        lmp::obj::generator::message_id_grammar<OutputIterator>                             message_id;
        lmp::obj::config::generator::config_object_sequence_grammar<OutputIterator>         config_object_sequence;
        karma::rule<OutputIterator, ast::Config()>                                          config_msg_rule;
      };
    }
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_CONFIG_GENERATOR_HPP_ */
