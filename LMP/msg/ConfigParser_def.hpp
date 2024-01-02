#ifndef LMP_MSG_CONFIG_PARSER_DEF_HPP_
#define LMP_MSG_CONFIG_PARSER_DEF_HPP_
/*
 * ConfigParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "ConfigAstAdapted.hpp"
#include "ConfigParser.hpp"
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
      config_msg_grammar<Iterator>::config_msg_grammar()
      : config_msg_grammar<Iterator>::base_type(config_msg_rule, "config_msg")
      {
        using qi::byte_;
        using qi::big_word;
        using qi::_a;
        using qi::_1;
        using qi::attr;
        using qi::omit;
        using phoenix::at_c;
        using namespace qi::labels;

        config_msg_rule %=
            attr(_r1)
            >> omit[ common_header_length [ _a = _1 ] ]
            >> local_ccid
            >> message_id
            >> local_node_id
            >> config_object_sequence(_a -
                                      c_headerLength -
                                      phx_getCCIdLength(at_c<1>(_val)) -
                                      phx_getMessageIdLength(at_c<2>(_val)) -
                                      phx_getNodeIdLength(at_c<3>(_val)))
                                      ;

        config_msg_rule.name("config_msg");
      }
    } // namespace parse
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_CONFIG_PARSER_DEF_HPP_ */
