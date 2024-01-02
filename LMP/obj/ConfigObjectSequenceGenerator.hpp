#ifndef LMP_OBJ_CONFIG_OBJECT_SEQUENCE_GENERATOR_HPP_
#define LMP_OBJ_CONFIG_OBJECT_SEQUENCE_GENERATOR_HPP_
/*
 * ConfigObjectSequenceGenerator.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ConfigObjectSequenceAst.hpp"
#include "obj/ConfigCTypesGenerator.hpp"

#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace obj
  {
    namespace config
    {
      namespace generator
      {
        namespace karma = boost::spirit::karma;
        template <typename OutputIterator>
        struct config_object_sequence_grammar : karma::grammar<OutputIterator, ast::ConfigObjectSequence()>
        {
          config_object_sequence_grammar();

          lmp::obj::config::generator::config_ctypes_grammar<OutputIterator>    config_object;
          karma::rule<OutputIterator, ast::ConfigObjectSequence()>              config_object_sequence;
        };
      }
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_CONFIG_OBJECT_SEQUENCE_GENERATOR_HPP_ */
