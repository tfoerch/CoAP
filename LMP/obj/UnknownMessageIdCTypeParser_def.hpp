#ifndef LMP_OBJ_UNKNOWN_MESSAGE_ID_PARSER_DEF_HPP_
#define LMP_OBJ_UNKNOWN_MESSAGE_ID_PARSER_DEF_HPP_
/*
 * UnknownMessageIdCTypeParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/UnknownMessageIdCTypeParser.hpp"
#include "obj/UnknownMessageIdCTypeAst.hpp"
#include "obj/ObjectClassUnknownCTypeAstAdapted.hpp"
#include "obj/ObjectHeaderUnknownCTypeParser_def.hpp"
#include "obj/ObjectClassAst.hpp"
#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>
#include <boost/spirit/home/x3/binary/binary.hpp>
#include <boost/spirit/home/x3.hpp>

#include <type_traits>

namespace lmp
{
  namespace obj
  {
    namespace parser
    {
      namespace x3 = boost::spirit::x3;
      namespace fusion = boost::fusion;
      using x3::big_dword;
      using x3::get;
      using x3::with;
      using fusion::at_c;

      ///////////////////////////////////////////////////////////////////////////
      // Rules
      ///////////////////////////////////////////////////////////////////////////

      unknown_message_id_ctype_type const unknown_message_id_ctype = "unknown_message_id_ctype";


      ///////////////////////////////////////////////////////////////////////////
      // Grammar
      ///////////////////////////////////////////////////////////////////////////
      lmp::WORD unknown_message_id_ctype_obj_length;

      auto header = [&](auto &ctx) { at_c<0>(_val(ctx)) = _attr(ctx); };
      auto push_back = [](auto &ctx) { at_c<1>(_val(ctx)).push_back(_attr(ctx)); };
      auto more   = [](auto &ctx) { _pass(ctx) = get<ObjLength>(ctx) >  at_c<1>(_val(ctx)).size() + lmp::obj::c_objHeaderLength; };
      auto done   = [](auto &ctx) { _pass(ctx) = get<ObjLength>(ctx) == at_c<1>(_val(ctx)).size() + lmp::obj::c_objHeaderLength; };

      auto const unknown_message_id_ctype_def =
        with<ObjLength>(std::ref(unknown_message_id_ctype_obj_length))
        [
          object_header_unknown_ctype<ObjectClass::MessageID> [header]  // class type
          >> *( eps [more] >> byte_[push_back] ) >> eps [done] // data
        ];

      BOOST_SPIRIT_DEFINE(unknown_message_id_ctype);

      ///////////////////////////////////////////////////////////////////////////
      // Annotation and Error handling
      ///////////////////////////////////////////////////////////////////////////

      // We want error-handling only for the start (outermost) rexpr
      // rexpr is the same as rexpr_inner but without error-handling (see error_handler.hpp)
      struct unknown_message_id_ctype_class : x3::annotate_on_success/*, error_handler_base*/ {};
    } // namespace parser

    parser::unknown_message_id_ctype_type const& unknown_message_id_ctype()
    {
      return parser::unknown_message_id_ctype;
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_UNKNOWN_MESSAGE_ID_PARSER_DEF_HPP_ */
