#ifndef LMP_BASE_EVENTFTORIF_HPP_
#define LMP_BASE_EVENTFTORIF_HPP_
/*
 * EventFtorIF.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <boost/utility.hpp>

namespace lmp
{
  namespace base
  {
    class EventFtorIF : boost::noncopyable
    {
    public:
      inline void operator()() const { do_process(); }
      virtual ~EventFtorIF(){}
    private:
      virtual bool do_process() const = 0;
    };
  } // namespace base
} // namespace lmp

#endif /* LMP_BASE_EVENTFTORIF_HPP_ */
