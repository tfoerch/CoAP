#ifndef LMP_OBJ_CONFIG_CTYPES_GENERATOR_HPP_
#define LMP_OBJ_CONFIG_CTYPES_GENERATOR_HPP_
/*
 * ConfigCTypesGenerator.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/HelloConfigGenerator.hpp"
#include "obj/ObjectClassUnknownCTypeGenerator.hpp"
#include "obj/ConfigCTypesAst.hpp"

#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace obj
  {
    namespace config
    {
      lmp::DWORD getLength(
        const ast::ConfigCTypes&  controlChannelIdCTypes);
      std::ostream& operator<<(
        std::ostream&                       os,
        const ast::ConfigCTypes&  controlChannelIdCTypes);
      namespace generator
      {
        namespace karma = boost::spirit::karma;
        template <typename OutputIterator>
        struct config_ctypes_grammar : karma::grammar<OutputIterator, ast::ConfigCTypes()>
        {
          config_ctypes_grammar();

          lmp::obj::generator::hello_config_grammar<OutputIterator>                              hello_config;
          lmp::obj::generator::object_class_unknown_ctype_grammar<OutputIterator,
                                                                 lmp::obj::ObjectClass::Config>  unknown_config_ctype;
          karma::rule<OutputIterator, ast::ConfigCTypes()>                                       config_ctypes_rule;
        };
      }
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_CONFIG_CTYPES_GENERATOR_HPP_ */
