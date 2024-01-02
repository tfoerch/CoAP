/*
 * Test_NeighborDiscoveredCheckFtor.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "Test_NeighborDiscoveredCheckFtor.hpp"
#include "neighbor/NeighborFactoryIF.hpp"

#include <iostream>

namespace lmp
{
  namespace cc
  {
    namespace test
    {
      NeighborDiscoveredCheckFtor::NeighborDiscoveredCheckFtor(
        const neighbor::NeighborFactoryIF&  node,
        lmp::DWORD                          neighborNodeId)
      : m_node(node),
        m_neighborNodeId(neighborNodeId)
      {}
      NeighborDiscoveredCheckFtor::NeighborDiscoveredCheckFtor(
        const NeighborDiscoveredCheckFtor&  other)
      : m_node(other.m_node),
        m_neighborNodeId(other.m_neighborNodeId)
      {}
      bool NeighborDiscoveredCheckFtor::do_check() const
      {
        std::cout << "NeighborDiscoveredCheckFtor::do_check" << std::endl;
        return
          ( m_node.getNeighbor(m_neighborNodeId) );
      }
      base::CheckFtorIF* NeighborDiscoveredCheckFtor::do_clone() const
      {
        return new NeighborDiscoveredCheckFtor(*this);
      }
    }
  } // namespace cc
} // namespace lmp
