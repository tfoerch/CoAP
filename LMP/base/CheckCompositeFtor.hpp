#ifndef LMP_BASE_CHECK_COMPOSITE_FTOR_HPP_
#define LMP_BASE_CHECK_COMPOSITE_FTOR_HPP_
/*
 * CheckCompositeFtor.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <CheckFtorIF.hpp>

namespace lmp
{
  namespace base
  {
    class CheckAndCompositeFtor : public CheckFtorIF
    {
    public:
      CheckAndCompositeFtor(
        const CheckFtorIF&   	        checkFtor1,
        const CheckFtorIF&              checkFtor2);
      CheckAndCompositeFtor(
        const CheckAndCompositeFtor&    other);
      virtual ~CheckAndCompositeFtor();
    private:
      virtual bool do_check() const;
      virtual CheckFtorIF* do_clone() const;
      const CheckFtorIF&              m_checkFtor1;
      const CheckFtorIF&              m_checkFtor2;
    };

    class CheckOrCompositeFtor : public CheckFtorIF
    {
    public:
      CheckOrCompositeFtor(
        const CheckFtorIF&              checkFtor1,
        const CheckFtorIF&              checkFtor2);
      CheckOrCompositeFtor(
        const CheckOrCompositeFtor&     other);
      virtual ~CheckOrCompositeFtor();
    private:
      virtual bool do_check() const;
      virtual CheckFtorIF* do_clone() const;
      const CheckFtorIF&              m_checkFtor1;
      const CheckFtorIF&              m_checkFtor2;
    };
  } // namespace base
} // namespace lmp

#endif /* LMP_BASE_CHECK_COMPOSITE_FTOR_HPP_ */
