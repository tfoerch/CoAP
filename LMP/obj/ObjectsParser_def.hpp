#ifndef LMP_OBJ_OBJECTS_PARSER_DEF_HPP_
#define LMP_OBJ_OBJECTS_PARSER_DEF_HPP_
/*
 * ObjectsParser_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectsParser.hpp"
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
    namespace parser
    {
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename Iterator>
      objects_grammar<Iterator>::objects_grammar()
      : objects_grammar::base_type(objects,
                                   "objects")
      {
        using qi::big_word;
        using qi::big_dword;
        using qi::_1;
        // using qi::debug;
        using phoenix::at_c;
        using namespace qi::labels;

        objects %=
            control_channel_id_ctypes |
            message_id_ctypes |
            node_id_ctypes |
            config_ctypes |
            hello_ctypes |
            unknown_object_class
            ;

        objects.name("objects");

        // debug(objects);
      }
    } // namespace parse
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTS_PARSER_DEF_HPP_ */
