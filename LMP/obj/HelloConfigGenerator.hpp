#ifndef LMP_OBJ_HELLO_CONFIG_GENERATOR_HPP_
#define LMP_OBJ_HELLO_CONFIG_GENERATOR_HPP_
/*
 * HelloConfigGenerator.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/HelloConfigAst.hpp"
#include "obj/ObjectHeaderGenerator.hpp"

#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace obj
  {
//    lmp::DWORD getLength(
//      const config::ast::HelloConfig&  localNodeId);
//    struct GetLengthHelloConfig
//    {
//      template<typename> struct result { typedef lmp::WORD type; };
//      lmp::WORD operator()(
//        const config::ast::HelloConfig& localNodeId) const
//      {
//        return getLength(localNodeId);
//      }
//    };
    namespace generator
    {
      namespace karma = boost::spirit::karma;
      template <typename OutputIterator>
      struct hello_config_grammar : karma::grammar<OutputIterator, config::ast::HelloConfig()>
      {
        hello_config_grammar();

        boost::phoenix::function<ast::GetLength<config::ast::HelloConfig>>   phx_getLength;
        lmp::obj::generator::object_header_grammar<OutputIterator, config::ClassType, config::ClassType::HelloConfig> object_header;
        karma::rule<OutputIterator, config::ast::HelloConfig()>  hello_config_rule;
      };
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLO_CONFIG_GENERATOR_HPP_ */
