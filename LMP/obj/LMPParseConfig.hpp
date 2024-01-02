#ifndef LMP_PARSE_CONFIG_HPP_
#define LMP_PARSE_CONFIG_HPP_
/*
 * LMPParseConfig.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/LMPParseErrorHandler.hpp"

#include <boost/spirit/home/x3/directive/with.hpp>
//#include <boost/spirit/home/x3.hpp>

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

namespace lmp
{
  namespace obj
  {
    namespace parser
    {
      struct ObjLength{};
      typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  iterator_type;
      typedef error_handler<iterator_type> error_handler_type;
      typedef x3::with_context<error_handler_tag,
                               std::reference_wrapper<error_handler_type> const>::type  context_type;
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_PARSE_CONFIG_HPP_ */
