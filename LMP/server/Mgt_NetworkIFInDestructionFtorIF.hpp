#ifndef Server_NetworkIFInDestructionFtorIF_HPP_
#define Server_NetworkIFInDestructionFtorIF_HPP_
/*
 * Mgt_NetworkIFInDestructionFtorIF.hpp
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"                  // for DWORD
#include <string>

namespace lmp_node
{

  class NetworkIFInDestructionFtorIF
  {
  public:
    inline void operator()(
      const std::string&  ifName,
      lmp::WORD           localPortNumber)
    { do_process(ifName, localPortNumber); }
    virtual ~NetworkIFInDestructionFtorIF(){}
  private:
    virtual void do_process(
      const std::string&  ifName,
      lmp::WORD           localPortNumber) = 0;
  };

} // end namespace lmp_node

#endif /* Server_NetworkIFInDestructionFtorIF_HPP_ */
