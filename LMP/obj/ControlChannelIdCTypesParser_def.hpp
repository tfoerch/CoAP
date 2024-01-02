#ifndef LMP_OBJ_CC_ID_CTYPES_PARSER_DEF_HPP_
#define LMP_OBJ_CC_ID_CTYPES_PARSER_DEF_HPP_
/*
 * ControlChannelIdCTypesParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ControlChannelIdCTypesParser.hpp"
#ifdef USE_SPIRIT_X3_PARSER
#include "obj/UnknownCCIdCTypeParser_def.hpp"
#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>
#include <boost/spirit/home/x3.hpp>
#else
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/object/static_cast.hpp>
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
        namespace fusion = boost::fusion;

        ///////////////////////////////////////////////////////////////////////////
        // Rules
        ///////////////////////////////////////////////////////////////////////////

        control_channel_id_ctypes_type const control_channel_id_ctypes = "control_channel_id_ctypes";


        ///////////////////////////////////////////////////////////////////////////
        // Grammar
        ///////////////////////////////////////////////////////////////////////////

        auto const control_channel_id_ctypes_def =
          local_cc_id |
          remote_cc_id |
          unknown_cc_id_ctype
          ;

        BOOST_SPIRIT_DEFINE(control_channel_id_ctypes);

        ///////////////////////////////////////////////////////////////////////////
        // Annotation and Error handling
        ///////////////////////////////////////////////////////////////////////////

        // We want error-handling only for the start (outermost) rexpr
        // rexpr is the same as rexpr_inner but without error-handling (see error_handler.hpp)
        struct control_channel_id_ctypes_class : x3::annotate_on_success/*, error_handler_base*/ {};
#else
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;

        template <typename Iterator>
        control_channel_id_ctypes_grammar<Iterator>::control_channel_id_ctypes_grammar()
        : control_channel_id_ctypes_grammar::base_type(control_channel_id_ctypes_rule,
                                                       "control_channel_id_ctypes")
        {
          using qi::big_word;
          using qi::big_dword;
          using qi::_1;
          using phoenix::at_c;
          using namespace qi::labels;

          control_channel_id_ctypes_rule %=
              local_ccid |
              remote_ccid |
              unknown_ccid_ctype
              ;

          control_channel_id_ctypes_rule.name("control_channel_id_ctypes");
        }
#endif /* USE_SPIRIT_X3_PARSER */
      } // namespace parser

#ifdef USE_SPIRIT_X3_PARSER
      parser::control_channel_id_ctypes_type const& control_channel_id_ctypes()
      {
        return parser::control_channel_id_ctypes;
      }
#endif /* USE_SPIRIT_X3_PARSER */
    } // namespace ccid
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_CC_ID_CTYPES_PARSER_DEF_HPP_ */
