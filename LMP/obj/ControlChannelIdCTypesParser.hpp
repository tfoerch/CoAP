#ifndef LMP_OBJ_CC_ID_CTYPES_PARSER_HPP_
#define LMP_OBJ_CC_ID_CTYPES_PARSER_HPP_
/*
 * ControlChannelIdCTypesParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ControlChannelIdCTypesAst.hpp"

#ifdef USE_SPIRIT_X3_PARSER
#include <boost/spirit/home/x3/support/traits/is_variant.hpp>
#include <boost/spirit/home/x3/support/traits/tuple_traits.hpp>
#include <boost/spirit/home/x3/nonterminal/rule.hpp>
#else
#include "obj/LocalCCIdParser.hpp"
#include "obj/RemoteCCIdParser.hpp"
#include "obj/ObjectClassUnknownCTypeParser.hpp"
#include <boost/spirit/include/qi.hpp>
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

        struct control_channel_id_ctypes_class;
        typedef
          x3::rule<control_channel_id_ctypes_class, ccid::ast::ControlChannelIdCTypes>  control_channel_id_ctypes_type;
        BOOST_SPIRIT_DECLARE(control_channel_id_ctypes_type);
#else

        namespace qi = boost::spirit::qi;
        template <typename Iterator>
        struct control_channel_id_ctypes_grammar : qi::grammar<Iterator, ccid::ast::ControlChannelIdCTypes()>
        {
          control_channel_id_ctypes_grammar();

          lmp::obj::parser::local_cc_id_grammar<Iterator>                                      local_ccid;
          lmp::obj::parser::remote_cc_id_grammar<Iterator>                                     remote_ccid;
          lmp::obj::parser::object_class_unknown_ctype_grammar<Iterator,
                                                               ObjectClass::ControlChannelID>  unknown_ccid_ctype;
          qi::rule<Iterator, ccid::ast::ControlChannelIdCTypes()>                              control_channel_id_ctypes_rule;
        };
#endif /* USE_SPIRIT_X3_PARSER */
      }
#ifdef USE_SPIRIT_X3_PARSER
      parser::control_channel_id_ctypes_type const& control_channel_id_ctypes();
#endif /* USE_SPIRIT_X3_PARSER */
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_CC_ID_CTYPES_PARSER_HPP_ */
