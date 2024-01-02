/*
 * ControlChannelIdCTypesParser.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ControlChannelIdCTypesParser_def.hpp"
#ifdef USE_SPIRIT_X3_PARSER
#include "obj/LMPParseConfig.hpp"
#else
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>
#endif /* USE_SPIRIT_X3_PARSER */

namespace lmp
{
  namespace obj
  {
    namespace ccid
    {
      namespace parser
      {
#ifdef USE_SPIRIT_X3_PARSER
        namespace x3 = boost::spirit::x3;

        BOOST_SPIRIT_INSTANTIATE(
          control_channel_id_ctypes_type, lmp::obj::parser::iterator_type, lmp::obj::parser::context_type);
#else
        typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
        template struct control_channel_id_ctypes_grammar<BufIterType>;
#endif /* USE_SPIRIT_X3_PARSER */
      }
    }
  }
}

//typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
//template struct lmp::obj::ccid::parse::control_channel_id_ctypes_grammar<BufIterType>;
//typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
//template struct lmp::obj::ccid::generate::control_channel_id_ctypes_grammar<BufOutIterType>;
//
//namespace
//{
//  struct ControlChannelIdCTypes_GetLengthVisitor : boost::static_visitor<lmp::DWORD>
//  {
//    lmp::DWORD operator()(const lmp::obj::ccid::LocalCCIdData& localCCId) const
//    {
//      return lmp::obj::getLength(localCCId);
//    }
//    lmp::DWORD operator()(const lmp::obj::ccid::RemoteCCIdData& remoteCCId) const
//    {
//      return lmp::obj::getLength(remoteCCId);
//    }
//    lmp::DWORD operator()(const lmp::obj::ccid::UnknownCCIdCTypeData& unknownCCId) const
//    {
//      return lmp::obj::getLength(unknownCCId);
//    }
//  };
//  struct ControlChannelIdCTypes_Printer : boost::static_visitor<std::ostream&>
//  {
//    ControlChannelIdCTypes_Printer(std::ostream& os)
//    : m_os(os)
//    {}
//    std::ostream& operator()(const lmp::obj::ccid::LocalCCIdData& localCCId) const
//    {
//      m_os << localCCId;
//      return m_os;
//    }
//    std::ostream& operator()(const lmp::obj::ccid::RemoteCCIdData& remoteCCId) const
//    {
//      m_os << remoteCCId;
//      return m_os;
//    }
//    std::ostream& operator()(const lmp::obj::ccid::UnknownCCIdCTypeData& unknownCCId) const
//    {
//      m_os << unknownCCId;
//      return m_os;
//    }
//    std::ostream&   m_os;
//  };
//}
//
//lmp::DWORD lmp::obj::ccid::getLength(
//  const lmp::obj::ccid::ControlChannelIdCTypes&  controlChannelIdCTypes)
//{
//  return boost::apply_visitor(ControlChannelIdCTypes_GetLengthVisitor(), controlChannelIdCTypes);
//}
//
//std::ostream& lmp::obj::ccid::operator<<(
//  std::ostream&                                  os,
//  const lmp::obj::ccid::ControlChannelIdCTypes&  controlChannelIdCTypes)
//{
//  boost::apply_visitor(ControlChannelIdCTypes_Printer(os), controlChannelIdCTypes);
//  return os;
//}
