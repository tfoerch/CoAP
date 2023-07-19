#include "LabelOTN.hpp"

namespace label
{

LabelOTN::LabelOTN(ServiceType serviceType, const TributarySlots& tributarySlots)
: m_serviceType(serviceType),
  m_tributarySlots(tributarySlots)
{}

LabelOTN::LabelOTN(ServiceType serviceType, TributarySlots&& tributarySlots)
: m_serviceType(serviceType),
  m_tributarySlots(tributarySlots)
{}

ServiceType LabelOTN::getServiceType() const
{
  return m_serviceType;
}

auto LabelOTN::getTributarySlots() const -> TributarySlotsResult
{
  return m_tributarySlots;
}

void LabelOTN::encode(MsgBuffer&  buffer) const
{
}


}; // namespace label
