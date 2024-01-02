#ifndef LMP_MSG_CONFIG_GENERATOR_DEF_HPP_
#define LMP_MSG_CONFIG_GENERATOR_DEF_HPP_
/*
 * ConfigGenerator_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "ConfigAstAdapted.hpp"
#include "ConfigGenerator.hpp"
#include "msg/CommonHeaderGenerator_def.hpp" // no explicit template instantiation
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
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
      config_msg_grammar<OutputIterator>::config_msg_grammar()
      : config_msg_grammar::base_type(config_msg_rule, "config_msg")
      {
        using phoenix::at_c;
        using qi::byte_;
        using qi::big_word;
        using namespace qi::labels;

        config_msg_rule %=
            common_header(phx_msgLength(_val))
            << local_ccid
            << message_id
            << local_node_id
            << config_object_sequence
            ;

        config_msg_rule.name("config_msg");
      }
    } // namespace generator
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_CONFIG_GENERATOR_DEF_HPP_ */
