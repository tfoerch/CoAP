/*
 * ConfigObjectSequenceParser.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ConfigObjectSequenceParser_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::obj::config::parser::config_object_sequence_grammar<BufIterType>;

namespace lmp
{
  namespace obj
  {
    namespace ast
    {
      template <>
      lmp::DWORD getLength<config::ast::ConfigObjectSequence>(
        const config::ast::ConfigObjectSequence&  configObjectSequence)
      {
        lmp::DWORD length = 0;
        for (std::vector<lmp::obj::config::ast::ConfigCTypes>::const_iterator iter = configObjectSequence.begin();
             iter != configObjectSequence.end();
             ++iter)
        {
          length += lmp::obj::ast::getLength(*iter);
        }
        return length;
      }

      std::ostream& operator<<(
          std::ostream&                             os,
          const config::ast::ConfigObjectSequence&  configObjectSequence)
      {
        for (std::vector<lmp::obj::config::ast::ConfigCTypes>::const_iterator iter = configObjectSequence.begin();
             iter != configObjectSequence.end();
             ++iter)
        {
          if (iter != configObjectSequence.begin())
          {
            os << ", ";
          }
          os << *iter;
        }
        return os;
      }
    }
  }
}
