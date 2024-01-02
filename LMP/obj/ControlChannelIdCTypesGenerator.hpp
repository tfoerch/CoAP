#ifndef LMP_OBJ_CC_ID_CTYPES_GENERATOR_HPP_
#define LMP_OBJ_CC_ID_CTYPES_GENERATOR_HPP_
/*
 * ControlChannelIdCTypesGenerator.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/LocalCCIdGenerator.hpp"
#include "obj/RemoteCCIdGenerator.hpp"
#include "obj/ObjectClassUnknownCTypeGenerator.hpp"
#include "obj/ControlChannelIdCTypesAst.hpp"

#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace obj
  {
    namespace ccid
    {
      lmp::DWORD getLength(
        const ast::ControlChannelIdCTypes&  controlChannelIdCTypes);
      std::ostream& operator<<(
        std::ostream&                       os,
        const ast::ControlChannelIdCTypes&  controlChannelIdCTypes);
      namespace generator
      {
        namespace karma = boost::spirit::karma;
        template <typename OutputIterator>
        struct control_channel_id_ctypes_grammar : karma::grammar<OutputIterator, ast::ControlChannelIdCTypes()>
        {
          control_channel_id_ctypes_grammar();

          lmp::obj::generator::local_cc_id_grammar<OutputIterator>                                         local_ccid;
          lmp::obj::generator::remote_cc_id_grammar<OutputIterator>                                        remote_ccid;
          lmp::obj::generator::object_class_unknown_ctype_grammar<OutputIterator,
                                                                 lmp::obj::ObjectClass::ControlChannelID>  unknown_ccid_ctype;
          karma::rule<OutputIterator, ast::ControlChannelIdCTypes()>                                       control_channel_id_ctypes_rule;
        };
      }
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_CC_ID_CTYPES_GENERATOR_HPP_ */
