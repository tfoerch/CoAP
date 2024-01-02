/*
 * UDP_Msg_Handler.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "UDP_Msg_Handler.hpp"
#include "IPCC_Impl.hpp"
#include "NetworkIFSocketIF.hpp"
#include "node/NodeApplicationIF.hpp"
#include "msg/MessageParser.hpp"
#include "msg/MessageGenerator.hpp"
#include "neighbor/Neighbor.hpp"
#include <boost/asio/buffers_iterator.hpp>

namespace
{
  struct msg_variants_processor : boost::static_visitor<void>
  {
    explicit msg_variants_processor(
      lmp::cc::IpccMsgReceiveIF&           ipcc)
    : m_ipcc(ipcc)
    {}
    void operator()(const lmp::msg::ast::Config& config) const
    {
      m_ipcc.processReceivedMessage(config);
    }
    void operator()(const lmp::msg::ast::ConfigAck& configAck) const
    {
      m_ipcc.processReceivedMessage(configAck);
    }
    void operator()(const lmp::msg::ast::ConfigNack& configNack) const
    {
      m_ipcc.processReceivedMessage(configNack);
    }
    void operator()(const lmp::msg::ast::Hello& hello) const
    {
      m_ipcc.processReceivedMessage(hello);
    }
    void operator()(const lmp::msg::ast::UnknownMessage& unknownMessage) const
    {
      m_ipcc.processReceivedMessage(unknownMessage);
    }
    lmp::cc::IpccMsgReceiveIF&                      m_ipcc;
  };
}

namespace lmp
{
  namespace cc
  {
    UDPMsgHandler::UDPMsgHandler(
      node::NodeApplicationIF&           node)
    : m_node(node)
    {
    }
    void UDPMsgHandler::sendMessage(
      NetworkIFSocketIF&                     networkIFSocket,
      const boost::asio::ip::udp::endpoint&  destination_endpoint,
      const msg::ast::Message&               message)
    {
      typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
      const lmp::WORD msgLength = lmp::msg::ast::getLength(message);
      unsigned char sendSpace[msgLength];
      boost::asio::mutable_buffers_1 sendBuffer(sendSpace, msgLength);
      BufOutIterType  gen_begin = boost::asio::buffers_begin(sendBuffer);
      //BufOutIterType gen_last = boost::asio::buffers_end(emptyBuffer);
      lmp::msg::generator::message_grammar<BufOutIterType>  msgGenerateGrammar;
      if (generate(gen_begin,
                   msgGenerateGrammar,
                   message))
      {
        networkIFSocket.send(destination_endpoint, sendBuffer);
      }
    }

    void UDPMsgHandler::do_processReceivedMessage(
      NetworkIFSocketIF&                     networkIFSocket,
      boost::asio::io_context&               io_context,
      const boost::asio::ip::udp::endpoint&  sender_endpoint,
      boost::asio::const_buffers_1&          messageBuffer)
    {
      IpccMsgReceiveIF* ipccPtr =
        accessIpcc(sender_endpoint);
      if (!ipccPtr)
      {
        ipccPtr = createIpcc(sender_endpoint, networkIFSocket, io_context);
        if (ipccPtr)
        {
          IpccApplicationIF* ipccApplPtr =
            dynamic_cast<lmp::cc::IpccApplicationIF*>(ipccPtr);
          if (ipccApplPtr)
          {
            ipccApplPtr->enable();
          }
        }
      }
      if (ipccPtr)
      {
        using boost::spirit::qi::parse;
        typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
        BufIterType begin = boost::asio::buffers_begin(messageBuffer);
        BufIterType last = boost::asio::buffers_end(messageBuffer);
        lmp::msg::parser::message_grammar<BufIterType>  msgGrammar;
        lmp::msg::ast::Message parsedMessage;
        if (parse(begin,
                  last,
                  msgGrammar,
                  parsedMessage))
        {
          boost::apply_visitor(msg_variants_processor(*ipccPtr), parsedMessage);
        }
      }
    }

    IpccMsgReceiveIF const* UDPMsgHandler::do_getIpcc(
      const boost::asio::ip::udp::endpoint&  sender_endpoint) const
    {
      IPCCMap::const_iterator ipccIter = m_IPCCs.find(sender_endpoint);
      return
        ( ipccIter != m_IPCCs.end() ?
          ipccIter->second :
          0 );
    }

    IpccMsgReceiveIF* UDPMsgHandler::do_accessIpcc(
      const boost::asio::ip::udp::endpoint&  sender_endpoint)
    {
      IPCCMap::iterator ipccIter = m_IPCCs.find(sender_endpoint);
      return
        ( ipccIter != m_IPCCs.end() ?
          ipccIter->second :
          0 );
    }

    IpccMsgReceiveIF* UDPMsgHandler::do_createIpcc(
      const boost::asio::ip::udp::endpoint&  sender_endpoint,
      NetworkIFSocketIF&                     networkIFSocket,
      boost::asio::io_context&               io_context)
    {
      IPCCMap::iterator ipccIter = m_IPCCs.find(sender_endpoint);
      if (ipccIter == m_IPCCs.end())
      {
        IpccImpl*  ipccPtr =
          new IpccImpl(m_node.registerFreeLocalCCId(),
                       m_node,
                       networkIFSocket,
                       io_context,
                       sender_endpoint,
                       true);
        if (ipccPtr)
        {
          // ipccPtr->enable();
          ipccIter = m_IPCCs.insert(IPCCMap::value_type(sender_endpoint,
                                                        ipccPtr)).first;
        }
      }
      return
        ( ipccIter != m_IPCCs.end() ?
          ipccIter->second :
          0 );
    }

    bool UDPMsgHandler::do_removeIpcc(
      const boost::asio::ip::udp::endpoint&  sender_endpoint)
    {
      IPCCMap::iterator ipccIter = m_IPCCs.find(sender_endpoint);
      if (ipccIter != m_IPCCs.end())
      {
        IpccMsgReceiveIF* ipccPtr = ipccIter->second;
        if (ipccPtr)
        {
          IpccApplicationIF* ipccApplPtr =
            dynamic_cast<IpccApplicationIF*>(ipccPtr);
          if (ipccApplPtr)
          {
            m_node.releaseLocalCCId(ipccApplPtr->getLocalCCId());
          }
          delete ipccPtr;
        }
        m_IPCCs.erase(ipccIter);
        return true;
      }
      return false;
    }

  } // namespace cc
} // namespace lmp
