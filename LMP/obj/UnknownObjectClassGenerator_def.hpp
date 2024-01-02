#ifndef LMP_OBJ_UNKNOWN_OBJECT_CLASS_GENERATOR_DEF_HPP_
#define LMP_OBJ_UNKNOWN_OBJECT_CLASS_GENERATOR_DEF_HPP_
/*
 * UnknownObjectClassGenerator_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/UnknownObjectClassAstAdapted.hpp"
#include "obj/UnknownObjectClassGenerator.hpp"
#include "obj/ObjectHeaderUnknownObjectClassGenerator_def.hpp"
#include "obj/ObjectClassAst.hpp"
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
    lmp::DWORD getLength(
      const ast::UnknownObjectClass&  unknownObjectClass)
    {
      return
        ( c_objHeaderLength +
          unknownObjectClass.m_data.size() );
    }
    namespace generator
    {
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename OutputIterator>
      unknown_object_class_grammar<OutputIterator>::unknown_object_class_grammar()
      : unknown_object_class_grammar::base_type(unknown_object_class_rule, "unknown_object_class")
      {
        using qi::byte_;
        using qi::big_word;
        using qi::eps;
        using phoenix::at_c;
        using namespace qi::labels;

        unknown_object_class_rule =
            object_header(phx_getLength(_val)) //[ _1 = at_c<0>(_val) ]
            << *byte_ //[ _1 = at_c<1>(_val) ]
            ;

        unknown_object_class_rule.name("unknown_object_class");
      }
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_UNKNOWN_OBJECT_CLASS_GENERATOR_DEF_HPP_ */
