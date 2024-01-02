#ifndef LMP_OBJ_LOCAL_NODE_ID_GENERATOR_DEF_HPP_
#define LMP_OBJ_LOCAL_NODE_ID_GENERATOR_DEF_HPP_
/*
 * LocalNodeIdGenerator_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/LocalNodeIdAstAdapted.hpp"
#include "obj/LocalNodeIdGenerator.hpp"
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
    namespace generator
    {
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename OutputIterator>
      local_node_id_grammar<OutputIterator>::local_node_id_grammar()
      : local_node_id_grammar::base_type(local_node_id_rule, "local_node_id")
      {
        using qi::byte_;
        using qi::big_dword;
        using qi::eps;
        using phoenix::at_c;
        using namespace qi::labels;

        local_node_id_rule =
            object_header(phx_getLength(_val)) [ _1 = at_c<0>(_val) ]
            << big_dword [ _1 = at_c<1>(_val) ]
            ;

        local_node_id_rule.name("local_node_id");
      }
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_LOCAL_NODE_ID_GENERATOR_DEF_HPP_ */
