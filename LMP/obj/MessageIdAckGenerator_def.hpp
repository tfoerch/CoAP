#ifndef LMP_OBJ_MESSAGE_ID_ACK_GENERATOR_DEF_HPP_
#define LMP_OBJ_MESSAGE_ID_ACK_GENERATOR_DEF_HPP_
/*
 * MessageIdAckGenerator_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/MessageIdAckAstAdapted.hpp"
#include "obj/MessageIdAckGenerator.hpp"
#include "obj/ObjectClassAst.hpp"
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/object/static_cast.hpp>

#include <type_traits>

namespace lmp
{
  namespace obj
  {
//    lmp::DWORD getLength(
//      const msgid::ast::MessageIdAck&  localNodeId)
//    {
//      return
//        ( c_objHeaderLength +
//          localNodeId.m_data.size() );
//    }
    namespace generator
    {
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename OutputIterator>
      message_id_ack_grammar<OutputIterator>::message_id_ack_grammar()
      : message_id_ack_grammar::base_type(message_id_ack_rule, "message_id_ack")
      {
        using qi::byte_;
        using qi::big_dword;
        using qi::eps;
        using phoenix::at_c;
        using namespace qi::labels;

        message_id_ack_rule =
            object_header(phx_getLength(_val)) [ _1 = at_c<0>(_val) ]
            << big_dword [ _1 = at_c<1>(_val) ]
            ;

        message_id_ack_rule.name("message_id_ack");
      }
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_MESSAGE_ID_ACK_GENERATOR_DEF_HPP_ */
