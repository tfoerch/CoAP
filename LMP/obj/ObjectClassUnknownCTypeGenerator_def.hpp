#ifndef LMP_OBJ_OBJECTCLASS_UNKNOWN_CTYPE_GENERATOR_DEF_HPP_
#define LMP_OBJ_OBJECTCLASS_UNKNOWN_CTYPE_GENERATOR_DEF_HPP_
/*
 * ObjectClassUnknownCTypeGenerator_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectClassUnknownCTypeAstAdapted.hpp"
#include "obj/ObjectClassUnknownCTypeGenerator.hpp"
#include "obj/ObjectHeaderUnknownCTypeGenerator_def.hpp"
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
    namespace generator
    {
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename OutputIterator, ObjectClass objClass>
      object_class_unknown_ctype_grammar<OutputIterator, objClass>::object_class_unknown_ctype_grammar()
      : object_class_unknown_ctype_grammar::base_type(object_class_unknown_ctype_rule, "object_class_unknown_ctype")
      {
        using qi::byte_;
        using qi::big_word;
        using qi::big_dword;
        using qi::eps;
        using phoenix::at_c;
        using namespace qi::labels;

        object_class_unknown_ctype_rule =
            object_header(phx_getLength(_val)) //[ _1 = at_c<0>(_val) ]
            << *byte_ // [ _1 = at_c<1>(_val) ]
            ;

        object_class_unknown_ctype_rule.name("object_class_unknown_ctype");
      }
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTCLASS_UNKNOWN_CTYPE_GENERATOR_DEF_HPP_ */
