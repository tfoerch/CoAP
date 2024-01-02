#ifndef LMP_OBJ_MESSAGE_ID_GENERATOR_HPP_
#define LMP_OBJ_MESSAGE_ID_GENERATOR_HPP_
/*
 * MessageIdGenerator.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/MessageIdAst.hpp"
#include "obj/ObjectHeaderGenerator.hpp"

#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace obj
  {
//    lmp::DWORD getLength(
//      const msgid::ast::MessageId&  localNodeId);
//    struct GetLengthMessageId
//    {
//      template<typename> struct result { typedef lmp::WORD type; };
//      lmp::WORD operator()(
//        const msgid::ast::MessageId& localNodeId) const
//      {
//        return getLength(localNodeId);
//      }
//    };
    namespace generator
    {
      namespace karma = boost::spirit::karma;
      template <typename OutputIterator>
      struct message_id_grammar : karma::grammar<OutputIterator, msgid::ast::MessageId()>
      {
        message_id_grammar();

        boost::phoenix::function<ast::GetLength<msgid::ast::MessageId>>   phx_getLength;
        lmp::obj::generator::object_header_grammar<OutputIterator, msgid::ClassType, msgid::ClassType::MessageId> object_header;
        karma::rule<OutputIterator, msgid::ast::MessageId()>  message_id_rule;
      };
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_MESSAGE_ID_GENERATOR_HPP_ */
