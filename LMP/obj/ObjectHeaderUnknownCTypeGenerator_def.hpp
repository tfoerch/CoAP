#ifndef LMP_OBJ_OBJECTHEADER_UNKNOWN_CTYPE_GENERATOR_DEF_HPP_
#define LMP_OBJ_OBJECTHEADER_UNKNOWN_CTYPE_GENERATOR_DEF_HPP_
/*
 * ObjectHeaderUnknownCTypeGenerator_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectHeaderUnknownCTypeAstAdapted.hpp"
#include "obj/ObjectHeaderUnknownCTypeGenerator.hpp"
#include <boost/spirit/include/qi.hpp>
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
    template <typename   ObjClassTraits>
    lmp::DWORD getLength(
      const ast::ObjectHeaderUnknownCType<ObjClassTraits>&  objClassUnknownCTypeData)
    {
      return
        ( c_objHeaderLength +
          objClassUnknownCTypeData.m_data.size() );
    }
    namespace generator
    {
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename OutputIterator, ObjectClass objClass>
      object_header_unknown_ctype_grammar<OutputIterator, objClass>::object_header_unknown_ctype_grammar()
      : object_header_unknown_ctype_grammar::base_type(object_header_unknown_ctype_rule, "object_header_unknown_ctype")
      {
        using qi::byte_;
        using qi::big_word;
        using qi::big_dword;
        using qi::eps;
        using phoenix::at_c;
        using namespace qi::labels;

        object_header_unknown_ctype_rule =
            ( eps(at_c<1>(_val)) << byte_ [ _1 = ( at_c<0>(_val) | lmp::obj::c_negotiableMask ) ] |
              byte_ [ _1 = at_c<0>(_val) ] ) // class type
            << byte_ [ _1 = static_cast<typename std::underlying_type<ObjectClass>::type>(objClass) ] // object class
            << big_word [ _1 = _r1 ] // length
            ;

        object_header_unknown_ctype_rule.name("object_header_unknown_ctype");
      }
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTHEADER_UNKNOWN_CTYPE_GENERATOR_DEF_HPP_ */
