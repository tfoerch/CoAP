#ifndef LMP_OBJ_CONFIG_OBJECT_SEQUENCE_PARSER_DEF_HPP_
#define LMP_OBJ_CONFIG_OBJECT_SEQUENCE_PARSER_DEF_HPP_
/*
 * ConfigObjectSequenceParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ConfigObjectSequenceParser.hpp"
#include <boost/bind.hpp>
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/object/static_cast.hpp>

namespace lmp
{
  namespace obj
  {
    namespace config
    {
      namespace parser
      {
        namespace fusion = boost::fusion;
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;

        template <typename Iterator>
        config_object_sequence_grammar<Iterator>::config_object_sequence_grammar()
        : config_object_sequence_grammar::base_type(config_object_sequence,
                                                    "config_object_sequence")
        {
          using qi::_1;
          using qi::eps;
          using phoenix::at_c;
          using phoenix::push_back;
          using namespace qi::labels;

          config_object_sequence =
              config_object [ push_back(_val, _1)]
              >> *( eps (_r1 >= phx_getLength(_val)) >> config_object[push_back(_val, _1)] ) >> eps (_r1 == phx_getLength(_val))
              ;

          config_object_sequence.name("config_object_sequence");
        }
      } // namespace parser
    } // namespace config
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_CONFIG_OBJECT_SEQUENCE_PARSER_DEF_HPP_ */
