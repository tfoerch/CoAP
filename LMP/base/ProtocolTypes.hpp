#ifndef LIBS_PROTOCOLTYPES_HPP_
#define LIBS_PROTOCOLTYPES_HPP_
/*
 * ProtocolTypes.hpp
 *
 *  Created on: 23.02.2015
 *      Author: tom
 */

#include <boost/cstdint.hpp>

namespace lmp
{
  typedef boost::uint8_t  BYTE;
  typedef boost::uint16_t WORD;
  typedef boost::uint32_t DWORD;
  typedef boost::uint64_t QWORD;
} // namespace lmp

#endif /* LIBS_PROTOCOLTYPES_HPP_ */
