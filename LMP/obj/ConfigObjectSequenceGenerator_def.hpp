#ifndef LMP_OBJ_CONFIG_OBJECT_SEQUENCE_GENERATOR_DEF_HPP_
#define LMP_OBJ_CONFIG_OBJECT_SEQUENCE_GENERATOR_DEF_HPP_
/*
 * ConfigObjectSequenceGenerator_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ConfigObjectSequenceGenerator.hpp"
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
      namespace generator
      {
        namespace fusion = boost::fusion;
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;

        template <typename OutputIterator>
        config_object_sequence_grammar<OutputIterator>::config_object_sequence_grammar()
        : config_object_sequence_grammar::base_type(config_object_sequence, "config_object_sequence")
        {
          using phoenix::at_c;
          using namespace qi::labels;

          config_object_sequence %=
              +config_object
              ;

          config_object_sequence.name("config_object_sequence");
        }
      } // namespace generate
    } // namespace config
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_CONFIG_OBJECT_SEQUENCE_GENERATOR_DEF_HPP_ */
