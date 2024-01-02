#ifndef LMP_OBJ_HELLO_GENERATOR_HPP_
#define LMP_OBJ_HELLO_GENERATOR_HPP_
/*
 * HelloGenerator.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/HelloAst.hpp"
#include "obj/ObjectHeaderGenerator.hpp"

#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace obj
  {
//    lmp::DWORD getLength(
//      const hello::ast::Hello&  localHello);
//    struct GetLengthHello
//    {
//      template<typename> struct result { typedef lmp::WORD type; };
//      lmp::WORD operator()(
//        const hello::ast::Hello& localHello) const
//      {
//        return getLength(localHello);
//      }
//    };
    namespace generator
    {
      namespace karma = boost::spirit::karma;
      template <typename OutputIterator>
      struct hello_grammar : karma::grammar<OutputIterator, hello::ast::Hello()>
      {
        hello_grammar();

        boost::phoenix::function<ast::GetLength<hello::ast::Hello>>   phx_getLength;
        lmp::obj::generator::object_header_grammar<OutputIterator, hello::ClassType, hello::ClassType::Hello> object_header;
        karma::rule<OutputIterator, hello::ast::Hello()>  hello_rule;
      };
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_HELLO_GENERATOR_HPP_ */
