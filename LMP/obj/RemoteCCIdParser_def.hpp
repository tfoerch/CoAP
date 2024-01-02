#ifndef LMP_OBJ_REMOTE_CC_ID_PARSER_DEF_HPP_
#define LMP_OBJ_REMOTE_CC_ID_PARSER_DEF_HPP_
/*
 * RemoteCCIdParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/RemoteCCIdAstAdapted.hpp"
#include "obj/RemoteCCIdParser.hpp"
#include "obj/ObjectHeaderParser_def.hpp"
#include "obj/ObjectClassAst.hpp"
#ifdef USE_SPIRIT_X3_PARSER
#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>
#include <boost/spirit/home/x3/binary/binary.hpp>
#include <boost/spirit/home/x3.hpp>
#else
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/object/static_cast.hpp>
#endif /* USE_SPIRIT_X3_PARSER */

#include <type_traits>

namespace lmp
{
  namespace obj
  {
    namespace parser
    {
#ifdef USE_SPIRIT_X3_PARSER
      namespace x3 = boost::spirit::x3;
      namespace fusion = boost::fusion;
      using x3::big_dword;
      using x3::get;
      using x3::with;
      using fusion::at_c;

      ///////////////////////////////////////////////////////////////////////////
      // Rules
      ///////////////////////////////////////////////////////////////////////////

      remote_cc_id_type const remote_cc_id = "remote_cc_id";


      ///////////////////////////////////////////////////////////////////////////
      // Grammar
      ///////////////////////////////////////////////////////////////////////////
//      lmp::WORD var_obj_length;

//      auto header = [&](auto &ctx) { at_c<0>(_val(ctx)) = _attr(ctx); };
//      auto ccId = [](auto &ctx) { at_c<1>(_val(ctx)) = _attr(ctx); };
//      auto checkLength = [](auto &ctx) { _pass(ctx) = get<ObjLength>(ctx) == HeaderCTypeTraits<ccid::ClassType, ccid::ClassType::RemoteCCId>::length; };

//      auto const remote_cc_id_def =
//        with<ObjLength>(std::ref(var_obj_length))
//        [
//          object_header_var_length<ccid::ClassType, ccid::ClassType::RemoteCCId> [header]
//          >> eps [checkLength]
//          >> big_dword [ccId]
//        ];

      auto const remote_cc_id_def =
        object_header_fix_length<ccid::ClassType, ccid::ClassType::RemoteCCId> // [header]
        >> big_dword //[ccId]
        ;

      BOOST_SPIRIT_DEFINE(remote_cc_id);

      ///////////////////////////////////////////////////////////////////////////
      // Annotation and Error handling
      ///////////////////////////////////////////////////////////////////////////

      // We want error-handling only for the start (outermost) rexpr
      // rexpr is the same as rexpr_inner but without error-handling (see error_handler.hpp)
      struct remote_cc_id_class : x3::annotate_on_success/*, error_handler_base*/ {};
#else
      namespace qi = boost::spirit::qi;
      template <typename Iterator>
      remote_cc_id_grammar<Iterator>::remote_cc_id_grammar()
      : remote_cc_id_grammar::base_type(remote_cc_id_rule,
                                       "remote_cc_id")
      {
        using qi::big_dword;
        using qi::_1;
        // using phoenix::at_c;
        using namespace qi::labels;

        remote_cc_id_rule =
          object_header
          >> big_dword // [ at_c<0>(_val) = _1 ]
          ;

        remote_cc_id_rule.name("remote_cc_id");
      }
#endif /* USE_SPIRIT_X3_PARSER */
    } // namespace parser

#ifdef USE_SPIRIT_X3_PARSER
    parser::remote_cc_id_type const& remote_cc_id()
    {
      return parser::remote_cc_id;
    }
#endif /* USE_SPIRIT_X3_PARSER */
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_REMOTE_CC_ID_PARSER_DEF_HPP_ */
