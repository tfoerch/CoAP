/*
 * CheckCompositeFtor.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "CheckCompositeFtor.hpp"

namespace coap
{
  namespace base
  {
    CheckAndCompositeFtor::CheckAndCompositeFtor(
      const CheckFtorIF&              checkFtor1,
      const CheckFtorIF&              checkFtor2)
      : m_checkFtor1(checkFtor1),
        m_checkFtor2(checkFtor2)
    {
    }

    bool CheckAndCompositeFtor::do_check() const
    {
      return (m_checkFtor1() && m_checkFtor2());
    }

    CheckOrCompositeFtor::CheckOrCompositeFtor(
      const CheckFtorIF&              checkFtor1,
      const CheckFtorIF&              checkFtor2)
      : m_checkFtor1(checkFtor1),
        m_checkFtor2(checkFtor2)
    {
    }

    bool CheckOrCompositeFtor::do_check() const
    {
      return (m_checkFtor1() || m_checkFtor2());
    }

  } // namespace cc
} // namespace lmp
