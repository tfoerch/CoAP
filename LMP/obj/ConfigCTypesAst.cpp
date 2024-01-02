/*
 * ConfigCTypesAst.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ConfigCTypesAst.hpp"

namespace
{
  struct ConfigCTypes_GetBodyLengthVisitor : boost::static_visitor<lmp::DWORD>
  {
    lmp::DWORD operator()(const lmp::obj::config::ast::HelloConfig& helloConfig) const
    {
      return lmp::obj::ast::getBodyLength(helloConfig);
    }
    lmp::DWORD operator()(const lmp::obj::config::ast::UnknownConfigCType& unknownConfig) const
    {
      return lmp::obj::getBodyLength(unknownConfig);
    }
  };
  struct ConfigCTypes_Printer : boost::static_visitor<std::ostream&>
  {
    ConfigCTypes_Printer(std::ostream& os)
    : m_os(os)
    {}
    std::ostream& operator()(const lmp::obj::config::ast::HelloConfig& helloConfig) const
    {
      m_os << helloConfig;
      return m_os;
    }
    std::ostream& operator()(const lmp::obj::config::ast::UnknownConfigCType& unknownConfig) const
    {
      m_os << unknownConfig;
      return m_os;
    }
    std::ostream&   m_os;
  };
}

namespace lmp
{
  namespace obj
  {
    namespace config
    {
      namespace ast
      {
        std::ostream& operator<<(
          std::ostream&        os,
          const ConfigCTypes&  configCType)
        {
          boost::apply_visitor(ConfigCTypes_Printer(os), configCType);
          return os;
        }
      }
    }
    namespace ast
    {
      template <>
      lmp::DWORD getBodyLength<config::ast::ConfigCTypes>(
        const config::ast::ConfigCTypes&  configCType)
      {
        return boost::apply_visitor(ConfigCTypes_GetBodyLengthVisitor(), configCType);
      }
    }
  }
}
