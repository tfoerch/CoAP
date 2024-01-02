#ifndef TEST_NEIGHBORDISCOVEREDCheckFtor_HPP_
#define TEST_NEIGHBORDISCOVEREDCheckFtor_HPP_
/*
 * Test_NeighborDiscoveredCheckFtor.hpp
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"                  // for DWORD
#include "base/CheckFtorIF.hpp"

namespace lmp
{
  namespace neighbor
  {
    class NeighborFactoryIF;
  }
  namespace cc
  {
    namespace test
    {
      class NeighborDiscoveredCheckFtor : public lmp::base::CheckFtorIF
      {
      public:
        NeighborDiscoveredCheckFtor(
          const neighbor::NeighborFactoryIF&  node,
          lmp::DWORD                          neighborNodeId);
        NeighborDiscoveredCheckFtor(
          const NeighborDiscoveredCheckFtor&  other);
      private:
        virtual bool do_check() const;
        virtual CheckFtorIF* do_clone() const;
        const neighbor::NeighborFactoryIF&  m_node;
        lmp::DWORD                          m_neighborNodeId;
      };
    };
  } // namespace cc
} // namespace lmp

#endif /* TEST_NEIGHBORDISCOVEREDCheckFtor_HPP_ */
