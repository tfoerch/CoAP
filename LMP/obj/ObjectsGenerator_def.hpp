#ifndef LMP_OBJ_OBJECTS_DEF_HPP_
#define LMP_OBJ_OBJECTS_DEF_HPP_
/*
 * ObjectsGenerator_def.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ObjectsGenerator.hpp"
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
    namespace generator
    {
      namespace fusion = boost::fusion;
      namespace phoenix = boost::phoenix;
      namespace qi = boost::spirit::qi;

      template <typename OutputIterator>
      objects_grammar<OutputIterator>::objects_grammar()
      : objects_grammar::base_type(objects, "objects")
      {
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
      }
    } // namespace generate
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_OBJECTS_DEF_HPP_ */
