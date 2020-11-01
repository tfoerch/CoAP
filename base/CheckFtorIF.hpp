#ifndef COAP_BASE_CHECKFTORIF_HPP_
#define COAP_BASE_CHECKFTORIF_HPP_
/*
 * CheckFtorIF.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

namespace coap
{
  namespace base
  {
    class CheckFtorIF
    {
    public:
      virtual ~CheckFtorIF() = default;
      inline bool operator()() const { return do_check(); }
    private:
      virtual bool do_check() const = 0;
    };
  } // namespace base
} // namespace coap

#endif /* COAP_BASE_CHECKFTORIF_HPP_ */
