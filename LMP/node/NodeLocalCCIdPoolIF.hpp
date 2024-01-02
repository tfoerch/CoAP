#ifndef LIBS_Node_LocalCCIdPoolIF_HPP_
#define LIBS_Node_LocalCCIdPoolIF_HPP_
/*
 * NodeLocalCCIdPoolIF.hpp
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"                  // for DWORD

namespace lmp
{
  namespace node
  {
    class NodeLocalCCIdPoolIF
    {
    public:
      inline lmp::DWORD registerFreeLocalCCId()
      { return do_registerFreeLocalCCId(); }
      inline bool isLocalCCIdFree(
        lmp::DWORD localCCId) const
      { return do_checkLocalCCId(localCCId); }
      inline bool registerLocalCCId(
        lmp::DWORD localCCId)
      { return do_registerLocalCCId(localCCId); }
      inline bool releaseLocalCCId(
        lmp::DWORD localCCId)
      { return do_releaseLocalCCId(localCCId); }
      virtual ~NodeLocalCCIdPoolIF(){}
   private:
      virtual lmp::DWORD do_registerFreeLocalCCId() = 0;
      virtual bool do_checkLocalCCId(
        lmp::DWORD localCCId) const = 0;
      virtual bool do_registerLocalCCId(
        lmp::DWORD localCCId) = 0;
      virtual bool do_releaseLocalCCId(
        lmp::DWORD localCCId) = 0;
    };
  } // namespace node
} // namespace lmp

#endif /* LIBS_Node_LocalCCIdPoolIF_HPP_ */
