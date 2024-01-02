#ifndef LMP_OBJ_MESSAGE_ID_ACK_GENERATOR_HPP_
#define LMP_OBJ_MESSAGE_ID_ACK_GENERATOR_HPP_
/*
 * MessageIdAckGenerator.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/MessageIdAckAst.hpp"
#include "obj/ObjectHeaderGenerator.hpp"

#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace obj
  {
//    lmp::DWORD getLength(
//      const msgid::ast::MessageIdAck&  localNodeId);
//    struct GetLengthMessageIdAck
//    {
//      template<typename> struct result { typedef lmp::WORD type; };
//      lmp::WORD operator()(
//        const msgid::ast::MessageIdAck& localNodeId) const
//      {
//        return getLength(localNodeId);
//      }
//    };
    namespace generator
    {
      namespace karma = boost::spirit::karma;
      template <typename OutputIterator>
      struct message_id_ack_grammar : karma::grammar<OutputIterator, msgid::ast::MessageIdAck()>
      {
        message_id_ack_grammar();

        boost::phoenix::function<ast::GetLength<msgid::ast::MessageIdAck>>   phx_getLength;
        lmp::obj::generator::object_header_grammar<OutputIterator, msgid::ClassType, msgid::ClassType::MessageIdAck> object_header;
        karma::rule<OutputIterator, msgid::ast::MessageIdAck()>  message_id_ack_rule;
      };
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_MESSAGE_ID_ACK_GENERATOR_HPP_ */
