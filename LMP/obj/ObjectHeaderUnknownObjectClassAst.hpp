#ifndef LMP_OBJ_OBJECTHEADER_UNKNOWN_OBJECT_CLASS_AST_HPP_
#define LMP_OBJ_OBJECTHEADER_UNKNOWN_OBJECT_CLASS_AST_HPP_
/*
 * ObjectHeaderUnknownObjectClassAst.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"

#ifdef USE_SPIRIT_X3_PARSER
#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#endif /* USE_SPIRIT_X3_PARSER */

namespace lmp
{
  namespace obj
  {
    namespace ast
    {
#ifdef USE_SPIRIT_X3_PARSER
      namespace x3 = boost::spirit::x3;
#endif /* USE_SPIRIT_X3_PARSER */

      struct ObjectHeaderUnknownObjectClass
#ifdef USE_SPIRIT_X3_PARSER
          : x3::position_tagged
#endif /* USE_SPIRIT_X3_PARSER */
      {
        lmp::BYTE               m_object_class;
        lmp::BYTE               m_class_type;
        bool                    m_negotiable;
      };
    } // namespace ast
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTHEADER_UNKNOWN_OBJECT_CLASS__AST_HPP_ */
