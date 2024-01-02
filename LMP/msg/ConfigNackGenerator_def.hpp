#ifndef LMP_MSG_CONFIGNACK_GENERATOR_DEF_HPP_
#define LMP_MSG_CONFIGNACK_GENERATOR_DEF_HPP_
/*
 * ConfigNackGenerator_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "ConfigNackAstAdapted.hpp"
#include "ConfigNackGenerator.hpp"
#include "CommonHeaderGenerator_def.hpp" // no explicit template instantiation
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/karma_attr_cast.hpp>
#include <boost/phoenix/object/static_cast.hpp>


namespace lmp
{
  namespace msg
  {
    namespace generator
    {
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename OutputIterator>
      config_nack_msg_grammar<OutputIterator>::config_nack_msg_grammar()
      : config_nack_msg_grammar::base_type(config_nack_msg_rule, "config_nack_msg")
      {
        using phoenix::at_c;
        using qi::byte_;
        using qi::big_word;
        using namespace qi::labels;

        config_nack_msg_rule %=
            common_header(phx_msgLength(_val))
            << local_ccid
            << local_node_id
            << remote_ccid
            << message_id_ack
            << remote_node_id
            << hello_config
            ;

        config_nack_msg_rule.name("config_nack_msg");
      }
    } // namespace generate
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_CONFIGNACK_GENERATOR_DEF_HPP_ */
