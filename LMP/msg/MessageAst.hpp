#ifndef LMP_MSG_MESSAGE_AST_HPP_
#define LMP_MSG_MESSAGE_AST_HPP_
/*
 * MessageAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "ConfigAst.hpp"
#include "ConfigAckAst.hpp"
#include "ConfigNackAst.hpp"
#include "HelloAst.hpp"
#include "UnknownMessageAst.hpp"

#include <boost/variant.hpp>
#include <iostream>

namespace lmp
{
  namespace msg
  {
    namespace ast
    {
      typedef
        boost::variant<Config,
                       ConfigAck,
                       ConfigNack,
                       Hello,
                       UnknownMessage>     Message;
      std::ostream& operator<<(
        std::ostream&    os,
        const Message&   message);
      lmp::WORD getLength(
        const Message&  message);
    }
  } // namespace msg
} // namespace lmp

#endif /* LMP_MSG_MESSAGE_AST_HPP_ */
