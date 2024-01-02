#ifndef LMP_OBJ_UNKNOWN_CONFIG_PARSER_DEF_HPP_
#define LMP_OBJ_UNKNOWN_CONFIG_PARSER_DEF_HPP_
/*
 * UnknownConfigCTypeParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/UnknownConfigCTypeParser.hpp"
#include "obj/UnknownConfigCTypeAst.hpp"
#include "obj/ObjectClassUnknownCTypeAstAdapted.hpp"
#include "obj/ObjectHeaderUnknownCTypeParser_def.hpp"
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

      unknown_config_ctype_type const unknown_config_ctype = "unknown_config_ctype";


      ///////////////////////////////////////////////////////////////////////////
      // Grammar
      ///////////////////////////////////////////////////////////////////////////
      lmp::WORD unknown_config_ctype_obj_length;

      auto header = [&](auto &ctx) { at_c<0>(_val(ctx)) = _attr(ctx); };
      auto push_back = [](auto &ctx) { at_c<1>(_val(ctx)).push_back(_attr(ctx)); };
      auto more   = [](auto &ctx) { _pass(ctx) = get<ObjLength>(ctx) >  at_c<1>(_val(ctx)).size() + lmp::obj::c_objHeaderLength; };
      auto done   = [](auto &ctx) { _pass(ctx) = get<ObjLength>(ctx) == at_c<1>(_val(ctx)).size() + lmp::obj::c_objHeaderLength; };

      auto const unknown_config_ctype_def =
        with<ObjLength>(std::ref(unknown_config_ctype_obj_length))
        [
          object_header_unknown_ctype<ObjectClass::Config> [header]  // class type
          >> *( eps [more] >> byte_[push_back] ) >> eps [done] // data
        ];

      BOOST_SPIRIT_DEFINE(unknown_config_ctype);

      ///////////////////////////////////////////////////////////////////////////
      // Annotation and Error handling
      ///////////////////////////////////////////////////////////////////////////

      // We want error-handling only for the start (outermost) rexpr
      // rexpr is the same as rexpr_inner but without error-handling (see error_handler.hpp)
      struct unknown_config_ctype_class : x3::annotate_on_success/*, error_handler_base*/ {};
#else
#endif /* USE_SPIRIT_X3_PARSER */
    } // namespace parser

#ifdef USE_SPIRIT_X3_PARSER
    parser::unknown_config_ctype_type const& unknown_config_ctype()
    {
      return parser::unknown_config_ctype;
    }
#endif /* USE_SPIRIT_X3_PARSER */
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_UNKNOWN_CONFIG_PARSER_DEF_HPP_ */
