#ifndef LMP_MSG_CONFIGACK_PARSER_DEF_HPP_
#define LMP_MSG_CONFIGACK_PARSER_DEF_HPP_
/*
 * ConfigAckParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "ConfigAckAstAdapted.hpp"
#include "ConfigAckParser.hpp"
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>


namespace lmp
{
  namespace msg
  {
    namespace parser
    {
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename Iterator>
      config_ack_msg_grammar<Iterator>::config_ack_msg_grammar()
      : config_ack_msg_grammar<Iterator>::base_type(config_ack_msg_rule, "config_ack_msg")
      {
        using qi::byte_;
        using qi::big_word;
        using qi::_a;
        using qi::_1;
        using qi::attr;
        using qi::omit;
        using phoenix::at_c;
        using namespace qi::labels;

        config_ack_msg_rule %=
            attr(_r1)
            >> omit[ common_header_length [ _a = _1 ] ]
            >> local_ccid
            >> local_node_id
            >> remote_ccid
            >> message_id_ack
            >> remote_node_id
            ;

        config_ack_msg_rule.name("config_ack_msg");
      }
    } // namespace parser
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_CONFIGACK_PARSER_DEF_HPP_ */
