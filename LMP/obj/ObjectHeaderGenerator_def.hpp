#ifndef LMP_OBJ_OBJECTHEADER_GENERATOR_DEF_HPP_
#define LMP_OBJ_OBJECTHEADER_GENERATOR_DEF_HPP_
/*
 * ObjectHeaderGenerator_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectHeaderGenerator.hpp"
#include "obj/ObjectHeaderAstAdapted.hpp"
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
//    template <typename   ObjCTypeTraits>
//    lmp::DWORD getLength(
//      const ast::ObjectHeaderTypeData<ObjCTypeTraits>&  objClassCTypeData)
//    {
//      return
//        ( c_objHeaderLength +
//          typename ObjCTypeTraits::get_length_ftor_type()(objClassCTypeData.m_data) );
//    }
    namespace generator
    {
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename OutputIterator, typename ClassType, ClassType ctype>
      object_header_grammar<OutputIterator, ClassType, ctype>::object_header_grammar()
      : object_header_grammar::base_type(object_header_rule, "object_header")
      {
        using qi::byte_;
        using qi::big_word;
        using qi::big_dword;
        using qi::eps;
        using phoenix::at_c;
        using namespace qi::labels;

        object_header_rule =
            (  eps(at_c<0>(_val)) << byte_ [ _1 = ( static_cast<typename std::underlying_type<ClassType>::type>(ctype) | lmp::obj::c_negotiableMask ) ] |
               byte_ [ _1 = static_cast<typename std::underlying_type<ClassType>::type>(ctype) ] ) // class type
            << byte_ [ _1 = static_cast<typename std::underlying_type<ObjectClass>::type>(HeaderObjClassTypeTraits<ClassType>::obj_class) ] // object class
            << big_word [ _1 = _r1 ] // length
            ;

        object_header_rule.name("object_header");
      }
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTHEADER_GENERATOR_DEF_HPP_ */
