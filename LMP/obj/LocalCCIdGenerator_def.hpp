#ifndef LMP_OBJ_LOCAL_CC_ID_GENERATOR_DEF_HPP_
#define LMP_OBJ_LOCAL_CC_ID_GENERATOR_DEF_HPP_
/*
 * LocalCCIdGenerator_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/LocalCCIdAstAdapted.hpp"
#include "obj/LocalCCIdGenerator.hpp"
#include "obj/ObjectClassAst.hpp"
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/qi.hpp>
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
//    lmp::DWORD getLength(
//      const ccid::ast::LocalCCId&  localCCId)
//    {
//      return
//        ( c_objHeaderLength +
//          localCCId.m_data.size() );
//    }
    namespace generator
    {
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename OutputIterator>
      local_cc_id_grammar<OutputIterator>::local_cc_id_grammar()
      : local_cc_id_grammar::base_type(local_cc_id_rule, "local_cc_id")
      {
        using qi::byte_;
        using qi::big_dword;
        using qi::eps;
        using phoenix::at_c;
        using namespace qi::labels;

        local_cc_id_rule =
            object_header(phx_getLength(_val)) [ _1 = at_c<0>(_val) ]
            << big_dword [ _1 = at_c<1>(_val) ]
            ;

        local_cc_id_rule.name("local_cc_id");
      }
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_LOCAL_CC_ID_GENERATOR_DEF_HPP_ */
