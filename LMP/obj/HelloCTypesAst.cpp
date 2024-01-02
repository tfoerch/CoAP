/*
 * HelloCTypesAst.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/HelloCTypesAst.hpp"

namespace
{
  struct HelloCTypes_GetBodyLengthVisitor : boost::static_visitor<lmp::DWORD>
  {
    lmp::DWORD operator()(const lmp::obj::hello::ast::Hello& hello) const
    {
      return lmp::obj::ast::getBodyLength(hello);
    }
    lmp::DWORD operator()(const lmp::obj::hello::ast::UnknownHelloCType& unknownHello) const
    {
      return lmp::obj::getBodyLength(unknownHello);
    }
  };
  struct HelloCTypes_Printer : boost::static_visitor<std::ostream&>
  {
    HelloCTypes_Printer(std::ostream& os)
    : m_os(os)
    {}
    std::ostream& operator()(const lmp::obj::hello::ast::Hello& hello) const
    {
      m_os << hello;
      return m_os;
    }
    std::ostream& operator()(const lmp::obj::hello::ast::UnknownHelloCType& unknownHello) const
    {
      m_os << unknownHello;
      return m_os;
    }
    std::ostream&   m_os;
  };
}

namespace lmp
{
  namespace obj
  {
    namespace hello
    {
      namespace ast
      {
        std::ostream& operator<<(
          std::ostream&                  os,
          const HelloCTypes&  helloCType)
        {
          boost::apply_visitor(HelloCTypes_Printer(os), helloCType);
          return os;
        }
      }
    }
    namespace ast
    {
      template <>
      lmp::DWORD getBodyLength<hello::ast::HelloCTypes>(
        const hello::ast::HelloCTypes&  helloCType)
      {
        return boost::apply_visitor(HelloCTypes_GetBodyLengthVisitor(), helloCType);
      }
    }
  }
}
