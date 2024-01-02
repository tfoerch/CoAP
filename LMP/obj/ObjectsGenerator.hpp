#ifndef LMP_OBJ_OBJECTS_GENERATOR_HPP_
#define LMP_OBJ_OBJECTS_GENERATOR_HPP_
/*
 * ObjectsGenerator.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectsAst.hpp"
#include "obj/ControlChannelIdCTypesGenerator.hpp"
#include "obj/MessageIdCTypesGenerator.hpp"
#include "obj/NodeIdCTypesGenerator.hpp"
#include "obj/ConfigCTypesGenerator.hpp"
#include "obj/HelloCTypesGenerator.hpp"
#include "obj/UnknownObjectClassGenerator.hpp"
#include <boost/spirit/include/karma.hpp>

namespace lmp
{
  namespace obj
  {
    namespace generator
    {
      namespace karma = boost::spirit::karma;
      template <typename OutputIterator>
      struct objects_grammar : karma::grammar<OutputIterator, ast::Objects()>
      {
        objects_grammar();

        lmp::obj::ccid::generator::control_channel_id_ctypes_grammar<OutputIterator>  control_channel_id_ctypes;
        lmp::obj::msgid::generator::message_id_ctypes_grammar<OutputIterator>         message_id_ctypes;
        lmp::obj::nodeid::generator::node_id_ctypes_grammar<OutputIterator>           node_id_ctypes;
        lmp::obj::config::generator::config_ctypes_grammar<OutputIterator>            config_ctypes;
        lmp::obj::hello::generator::hello_ctypes_grammar<OutputIterator>              hello_ctypes;
        lmp::obj::generator::unknown_object_class_grammar<OutputIterator>             unknown_object_class;
        karma::rule<OutputIterator, ast::Objects()>                                   objects;
      };
    }
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTS_GENERATOR_HPP_ */
