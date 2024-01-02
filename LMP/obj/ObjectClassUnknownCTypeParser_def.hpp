#ifndef LMP_OBJ_OBJECTCLASS_UNKNOWN_CTYPE_PARSER_DEF_HPP_
#define LMP_OBJ_OBJECTCLASS_UNKNOWN_CTYPE_PARSER_DEF_HPP_
/*
 * ObjectClassUnknownCTypeParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectClassUnknownCTypeAstAdapted.hpp"
#include "obj/ObjectClassUnknownCTypeParser.hpp"
#include "obj/ObjectHeaderUnknownCTypeParser_def.hpp"
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/object/static_cast.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <type_traits>

namespace lmp
{
  namespace obj
  {
    namespace parser
    {
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename Iterator, ObjectClass objClass>
      object_class_unknown_ctype_grammar<Iterator, objClass>::object_class_unknown_ctype_grammar()
      : object_class_unknown_ctype_grammar::base_type(object_class_unknown_ctype_rule, "object_class_unknown_ctype")
      {
        using qi::byte_;
        using qi::big_word;
        using qi::big_dword;
        using qi::eps;
        using qi::repeat;
        using phoenix::at_c;
        using namespace qi::labels;

        object_class_unknown_ctype_rule =
            object_header(_a) //[ _1 = at_c<0>(_val) ]
            >> repeat(_a - lmp::obj::c_objHeaderLength)[byte_]
//            >> *( eps(_a > at_c<1>(_val).size() + lmp::obj::c_objHeaderLength)
//                  >> byte_ [push_back(_val, _1)] )
//            >> eps(_a > at_c<1>(_val).size() + lmp::obj::c_objHeaderLength) // [ _1 = at_c<1>(_val) ]
            ;

        object_class_unknown_ctype_rule.name("object_class_unknown_ctype");
      }
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTCLASS_UNKNOWN_CTYPE_PARSER_DEF_HPP_ */
