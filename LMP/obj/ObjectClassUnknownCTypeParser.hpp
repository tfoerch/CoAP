#ifndef LMP_OBJ_OBJECTCLASS_UNKNOWN_CTYPE_PARSER_HPP_
#define LMP_OBJ_OBJECTCLASS_UNKNOWN_CTYPE_PARSER_HPP_
/*
 * ObjectClassUnknownCTypeParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectClassUnknownCTypeAst.hpp"
#include "obj/ObjectHeaderUnknownCTypeParser.hpp"
#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace obj
  {
    namespace parser
    {
      namespace qi = boost::spirit::qi;
      template <typename Iterator, ObjectClass objClass>
      struct object_class_unknown_ctype_grammar : qi::grammar<Iterator,
                                                              ast::ObjectClassUnknownCType<ObjectClassTraits<objClass>>(),
                                                              qi::locals<lmp::WORD>>
      {
        object_class_unknown_ctype_grammar();

//        boost::phoenix::function<GetLengthUnknownCType<ObjectClassTraits<objClass>>>     phx_getLength;
        lmp::obj::parser::object_header_unknown_ctype_grammar<Iterator, objClass>        object_header;
        qi::rule<Iterator,
                 ast::ObjectClassUnknownCType<ObjectClassTraits<objClass>>(),
                 qi::locals<lmp::WORD>>                                                  object_class_unknown_ctype_rule;
      };
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTCLASS_UNKNOWN_CTYPE_PARSER_HPP_ */
