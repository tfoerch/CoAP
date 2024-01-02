#ifndef LMP_OBJ_CC_ID_CTYPES_GENERATOR_DEF_HPP_
#define LMP_OBJ_CC_ID_CTYPES_DEF_GENERATOR_HPP_
/*
 * ControlChannelIdCTypesGenerator_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ControlChannelIdCTypesGenerator.hpp"
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/object/static_cast.hpp>

namespace lmp
{
  namespace obj
  {
    namespace ccid
    {
      namespace generator
      {
        namespace fusion = boost::fusion;
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;

        template <typename OutputIterator>
        control_channel_id_ctypes_grammar<OutputIterator>::control_channel_id_ctypes_grammar()
        : control_channel_id_ctypes_grammar::base_type(control_channel_id_ctypes_rule, "control_channel_id_ctypes")
        {
          using phoenix::at_c;
          using namespace qi::labels;

          control_channel_id_ctypes_rule %=
              local_ccid |
              remote_ccid |
              unknown_ccid_ctype
              ;

          control_channel_id_ctypes_rule.name("control_channel_id_ctypes");
        }
      } // namespace generate
    } // namespace ccid
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_CC_ID_CTYPES_GENERATOR_DEF_HPP_ */
