#ifndef COAP_BASE_CHECK_COMPOSITE_FTOR_HPP_
#define COAP_BASE_CHECK_COMPOSITE_FTOR_HPP_
/*
 * CheckCompositeFtor.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <CheckFtorIF.hpp>

namespace coap
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
        const CheckAndCompositeFtor&    other) = delete;
      ~CheckAndCompositeFtor() = default;
    private:
      virtual bool do_check() const;
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
        const CheckOrCompositeFtor&     other) = delete;
      virtual ~CheckOrCompositeFtor();
    private:
      virtual bool do_check() const;
      const CheckFtorIF&              m_checkFtor1;
      const CheckFtorIF&              m_checkFtor2;
    };
  } // namespace base
} // namespace coap

#endif /* COAP_BASE_CHECK_COMPOSITE_FTOR_HPP_ */
