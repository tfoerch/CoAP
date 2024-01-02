#ifndef LMP_OBJ_OBJECTHEADER_UNKNOWN_OBJECT_CLASS_GENERATOR_DEF_HPP_
#define LMP_OBJ_OBJECTHEADER_UNKNOWN_OBJECT_CLASS_GENERATOR_DEF_HPP_
/*
 * ObjectHeaderUnknownObjectClassGenerator_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectHeaderUnknownObjectClassAstAdapted.hpp"
#include "obj/ObjectHeaderUnknownObjectClassGenerator.hpp"
#include "obj/ObjectClassAst.hpp"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/object/static_cast.hpp>

#include <type_traits>

namespace lmp
{
  namespace obj
  {
    namespace generator
    {
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename OutputIterator>
      object_header_unknown_object_class_grammar<OutputIterator>::object_header_unknown_object_class_grammar()
      : object_header_unknown_object_class_grammar::base_type(object_header_unknown_object_class_rule, "object_header_unknown_object_class")
      {
        using qi::byte_;
        using qi::big_word;
        using qi::eps;
        using phoenix::at_c;
        using namespace qi::labels;

        object_header_unknown_object_class_rule =
            ( eps(at_c<2>(_val)) << byte_ [ _1 = ( at_c<1>(_val) | lmp::obj::c_negotiableMask ) ] |
              byte_ [ _1 = at_c<1>(_val) ] ) // class type
            << byte_ [ _1 = at_c<0>(_val) ] // object class
            << big_word [ _1 = _r1 ] // length
            ;

        object_header_unknown_object_class_rule.name("object_header_unknown_object_class");
      }
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTHEADER_UNKNOWN_OBJECT_CLASS_GENERATOR_DEF_HPP_ */
