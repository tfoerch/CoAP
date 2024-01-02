#ifndef LIBS_MSG_READHANDLERIF_HPP_
#define LIBS_MSG_READHANDLERIF_HPP_
/*
 * IPCC_Msg_ReceiveIF.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

// http://www.boost.org/doc/libs/1_57_0/libs/ptr_container/doc/guidelines.html
namespace boost { namespace system { class error_code; } }

namespace lmp
{
  namespace msg
  {
    class MsgReadHandlerIF
    {
    public:
      inline void operator()(
    	const boost::system::error_code& ec,
    	std::size_t                      bytes_transferred)  { do_processReceivedMessage(ec, bytes_transferred); }
      virtual ~MsgReadHandlerIF(){}
    private:
      virtual void do_processReceivedMessage(
    	const boost::system::error_code& ec,
    	std::size_t                      bytes_transferred) = 0;
    };
  } // namespace cc
} // namespace lmp

#endif /* LIBS_MSG_READHANDLERIF_HPP_ */
