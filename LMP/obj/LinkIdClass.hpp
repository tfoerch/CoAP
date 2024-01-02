#ifndef LMP_OBJ_LINK_ID_CLASS_HPP_
#define LMP_OBJ_LINK_ID_CLASS_HPP_
/*
 * LinkIdClass.hpp
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
    namespace linkid
    {
      enum class ClassType : lmp::BYTE
      {
        IPv4LocalLinkId = 1,
        IPv4RemoteLinkId,
        IPv6LocalLinkId,
        IPv6RemoteLinkId,
        UnnumberedLocalLinkId,
        UnnumberedRemoteLinkId
      };
      std::ostream& operator<<(
        std::ostream&     os,
        const ClassType&  cType);
    }
    template <>
    struct ObjectClassTypeConst<linkid::ClassType>
    {
      static const ObjectClass  obj_class = ObjectClass::LinkID;
    };
  } // namespace obj
} // namespace lmp

#endif /* LMP_OBJ_LINK_ID_CLASS_HPP_ */
