#ifndef Server_IPCCInDestructionFtorIF_HPP_
#define Server_IPCCInDestructionFtorIF_HPP_
/*
 * Mgt_IPCCInDestructionFtorIF.hpp
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"                  // for DWORD

namespace lmp_netif
{

  class IPCCInDestructionFtorIF
  {
  public:
    inline void operator()(
      lmp::DWORD                   remoteAddress,
      lmp::WORD                    remotePortNumber)
    { do_process(remoteAddress, remotePortNumber); }
    virtual ~IPCCInDestructionFtorIF(){}
  private:
    virtual void do_process(
      lmp::DWORD                   remoteAddress,
      lmp::WORD                    remotePortNumber) = 0;
  };

} // end namespace lmp_netif

#endif /* Server_IPCCInDestructionFtorIF_HPP_ */
