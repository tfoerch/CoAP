#ifndef LMP_OBJ_OBJECTS_PARSER_HPP_
#define LMP_OBJ_OBJECTS_PARSER_HPP_
/*
 * ObjectsParser.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectsAst.hpp"
#include "obj/ControlChannelIdCTypesParser.hpp"
#include "obj/MessageIdCTypesParser.hpp"
#include "obj/NodeIdCTypesParser.hpp"
#include "obj/ConfigCTypesParser.hpp"
#include "obj/HelloCTypesParser.hpp"
#include "obj/UnknownObjectClassParser.hpp"

#include <boost/spirit/include/qi.hpp>

namespace lmp
{
  namespace obj
  {
    namespace parser
    {
      namespace qi = boost::spirit::qi;
      template <typename Iterator>
      struct objects_grammar : qi::grammar<Iterator, ast::Objects()>
      {
        objects_grammar();

        lmp::obj::ccid::parser::control_channel_id_ctypes_grammar<Iterator>    control_channel_id_ctypes;
        lmp::obj::msgid::parser::message_id_ctypes_grammar<Iterator>           message_id_ctypes;
        lmp::obj::nodeid::parser::node_id_ctypes_grammar<Iterator>             node_id_ctypes;
        lmp::obj::config::parser::config_ctypes_grammar<Iterator>              config_ctypes;
        lmp::obj::hello::parser::hello_ctypes_grammar<Iterator>                hello_ctypes;
        lmp::obj::parser::unknown_object_class_grammar<Iterator>               unknown_object_class;
        qi::rule<Iterator, ast::Objects()>                                     objects;
      };
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTS_PARSER_HPP_ */
