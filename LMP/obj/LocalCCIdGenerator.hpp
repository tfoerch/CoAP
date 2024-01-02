#ifndef LMP_OBJ_LOCAL_CC_ID_GENERATOR_HPP_
#define LMP_OBJ_LOCAL_CC_ID_GENERATOR_HPP_
/*
 * LocalCCIdGenerator.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/LocalCCIdAst.hpp"
#include "obj/ObjectHeaderGenerator.hpp"

#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace obj
  {
//    lmp::DWORD getLength(
//      const ccid::ast::LocalCCId&  localCCId);
//    struct GetLengthLocalCCId
//    {
//      template<typename> struct result { typedef lmp::WORD type; };
//      lmp::WORD operator()(
//        const ccid::ast::LocalCCId& localCCId) const
//      {
//        return getLength(localCCId);
//      }
//    };
    namespace generator
    {
      namespace karma = boost::spirit::karma;
      template <typename OutputIterator>
      struct local_cc_id_grammar : karma::grammar<OutputIterator, ccid::ast::LocalCCId()>
      {
        local_cc_id_grammar();

        boost::phoenix::function<ast::GetLength<ccid::ast::LocalCCId>>   phx_getLength;
        lmp::obj::generator::object_header_grammar<OutputIterator, ccid::ClassType, ccid::ClassType::LocalCCId> object_header;
        karma::rule<OutputIterator, ccid::ast::LocalCCId()>  local_cc_id_rule;
      };
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_LOCAL_CC_ID_GENERATOR_HPP_ */
