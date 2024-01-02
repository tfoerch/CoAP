#ifndef LMP_BASE_CHECKFTORIF_HPP_
#define LMP_BASE_CHECKFTORIF_HPP_
/*
 * CheckFtorIF.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <boost/utility.hpp>

namespace lmp
{
  namespace base
  {
    class CheckFtorIF : boost::noncopyable
    {
    public:
      inline bool operator()() const { return do_check(); }
      inline CheckFtorIF* clone() const { return do_clone(); }
      virtual ~CheckFtorIF(){}
    private:
      virtual bool do_check() const = 0;
      virtual CheckFtorIF* do_clone() const = 0;
    };
  } // namespace base
} // namespace lmp

#endif /* LIBS_MSG_READHANDLERIF_HPP_ */
