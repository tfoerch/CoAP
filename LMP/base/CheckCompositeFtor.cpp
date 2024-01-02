/*
 * CheckCompositeFtor.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "CheckCompositeFtor.hpp"

namespace lmp
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

    CheckAndCompositeFtor::CheckAndCompositeFtor(
      const CheckAndCompositeFtor&      other)
    : m_checkFtor1(other.m_checkFtor1),
      m_checkFtor2(other.m_checkFtor2)
    {
    }
    CheckAndCompositeFtor::~CheckAndCompositeFtor()
    {
    }
    bool CheckAndCompositeFtor::do_check() const
    {
      return (m_checkFtor1() && m_checkFtor2());
    }

    CheckFtorIF* CheckAndCompositeFtor::do_clone() const
    {
      return new CheckAndCompositeFtor(*this);
    }

    CheckOrCompositeFtor::CheckOrCompositeFtor(
      const CheckFtorIF&              checkFtor1,
      const CheckFtorIF&              checkFtor2)
      : m_checkFtor1(checkFtor1),
        m_checkFtor2(checkFtor2)
    {
    }

    CheckOrCompositeFtor::CheckOrCompositeFtor(
      const CheckOrCompositeFtor&      other)
    : m_checkFtor1(other.m_checkFtor1),
      m_checkFtor2(other.m_checkFtor2)
    {
    }
    CheckOrCompositeFtor::~CheckOrCompositeFtor()
    {
    }
    bool CheckOrCompositeFtor::do_check() const
    {
      return (m_checkFtor1() || m_checkFtor2());
    }

    CheckFtorIF* CheckOrCompositeFtor::do_clone() const
    {
      return new CheckOrCompositeFtor(*this);
    }
  } // namespace cc
} // namespace lmp
