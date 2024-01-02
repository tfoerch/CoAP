/*
 * MessageType.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "MessageType.hpp"

std::ostream& lmp::msg::operator<<(
  std::ostream&              os,
  const lmp::msg::MsgType&   msgType)
{
  switch(msgType)
  {
    case lmp::msg::MsgType::Config:
      os << "Config";
      break;
    case lmp::msg::MsgType::ConfigAck:
      os << "ConfigAck";
      break;
    case lmp::msg::MsgType::ConfigNack:
      os << "ConfigNack";
      break;
    case lmp::msg::MsgType::Hello:
      os << "Hello";
      break;
  }
  return os;
}
