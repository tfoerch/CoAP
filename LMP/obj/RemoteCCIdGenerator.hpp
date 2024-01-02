#ifndef LMP_OBJ_REMOTE_CC_ID_GENERATOR_HPP_
#define LMP_OBJ_REMOTE_CC_ID_GENERATOR_HPP_
/*
 * RemoteCCIdGenerator.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/RemoteCCIdAst.hpp"
#include "obj/ObjectHeaderGenerator.hpp"

#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace obj
  {
//    lmp::DWORD getLength(
//      const ccid::ast::RemoteCCId&  remoteCCId);
//    struct GetLengthRemoteCCId
//    {
//      template<typename> struct result { typedef lmp::WORD type; };
//      lmp::WORD operator()(
//        const ccid::ast::RemoteCCId& remoteCCId) const
//      {
//        return getLength(remoteCCId);
//      }
//    };
    namespace generator
    {
      namespace karma = boost::spirit::karma;
      template <typename OutputIterator>
      struct remote_cc_id_grammar : karma::grammar<OutputIterator, ccid::ast::RemoteCCId()>
      {
        remote_cc_id_grammar();

        boost::phoenix::function<ast::GetLength<ccid::ast::RemoteCCId>>   phx_getLength;
        lmp::obj::generator::object_header_grammar<OutputIterator, ccid::ClassType, ccid::ClassType::RemoteCCId> object_header;
        karma::rule<OutputIterator, ccid::ast::RemoteCCId()>  remote_cc_id_rule;
      };
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_REMOTE_CC_ID_GENERATOR_HPP_ */
