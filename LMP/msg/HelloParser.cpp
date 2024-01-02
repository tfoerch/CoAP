/*
 * HelloParser.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "HelloParser_def.hpp"
//#include "MessageType_def.hpp"
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>
#include <iostream>

//const lmp::msg::MsgType lmp::msg::MessageTypeTraits<lmp::msg::MsgType::Hello>::msg_type_value = lmp::msg::MsgType::Hello;
typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::msg::parser::hello_msg_grammar<BufIterType>;
//template struct lmp::msg::parse::message_type_grammar<BufIterType, lmp::msg::MsgType::Hello>;

//namespace lmp
//{
//  namespace msg
//  {
//    namespace hello
//    {
//      lmp::WORD GetLengthFtor::operator()(
//        const HelloBody&  helloBody) const
//      {
//        return
//          ( lmp::obj::getLength(helloBody.m_hello)  );
//      }
//      bool IsEqualFtor::operator()(
//        const HelloBody&  first,
//        const HelloBody&  second) const
//      {
//        return
//          ( first.m_hello == second.m_hello );
//      }
//      std::ostream& operator<<(
//        std::ostream&     os,
//        const HelloBody&  helloBody)
//      {
//        std::cout << helloBody.m_hello;
//        return os;
//      }
//    }
//  } // namespace msg
//} // namespace lmp
