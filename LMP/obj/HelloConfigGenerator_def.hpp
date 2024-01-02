#ifndef LMP_OBJ_HELLO_CONFIG_GENERATOR_DEF_HPP_
#define LMP_OBJ_HELLO_CONFIG_GENERATOR_DEF_HPP_
/*
 * HelloConfigGenerator_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/HelloConfigAstAdapted.hpp"
#include "obj/HelloConfigGenerator.hpp"
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
//      const config::ast::HelloConfig&  localNodeId)
//    {
//      return
//        ( c_objHeaderLength +
//          localNodeId.m_data.size() );
//    }
    namespace generator
    {
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename OutputIterator>
      hello_config_grammar<OutputIterator>::hello_config_grammar()
      : hello_config_grammar::base_type(hello_config_rule, "hello_config")
      {
        using qi::byte_;
        using qi::big_word;
        using qi::eps;
        using phoenix::at_c;
        using namespace qi::labels;

        hello_config_rule =
            object_header(phx_getLength(_val)) [ _1 = at_c<0>(_val) ]
            << big_word [ _1 = at_c<1>(_val) ]
            << big_word [ _1 = at_c<2>(_val) ]
            ;

        hello_config_rule.name("hello_config");
      }
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLO_CONFIG_GENERATOR_DEF_HPP_ */
