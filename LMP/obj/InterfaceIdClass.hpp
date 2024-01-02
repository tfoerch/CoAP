#ifndef LMP_OBJ_INTERFACE_ID_CLASS_HPP_
#define LMP_OBJ_INTERFACE_ID_CLASS_HPP_
/*
 * InterfaceIdClass.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"
#include "obj/ObjectClass.hpp"

namespace lmp
{
  namespace obj
  {
    namespace ifid
    {
      enum class ClassType : lmp::BYTE
      {
        IPv4LocalInterfaceId = 1,
        IPv4RemoteInterfaceId,
        IPv6LocalInterfaceId,
        IPv6RemoteInterfaceId,
        UnnumberedLocalInterfaceId,
        UnnumberedRemoteInterfaceId
      };
      std::ostream& operator<<(
        std::ostream&     os,
        const ClassType&  cType);
    }
    template <>
    struct ObjectClassTypeConst<ifid::ClassType>
    {
      static const ObjectClass  obj_class = ObjectClass::InterfaceID;
    };
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_INTERFACE_ID_CLASS_HPP_ */
