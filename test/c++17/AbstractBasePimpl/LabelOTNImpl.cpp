#include "LabelOTNImpl.hpp"

namespace label::impl
{

LabelOTNImpl::LabelOTNImpl(ServiceType serviceType, const TributarySlots& tributarySlots)
: m_serviceType(serviceType),
  m_tributarySlots(tributarySlots)
{}

LabelOTNImpl::LabelOTNImpl(ServiceType serviceType, TributarySlots&& tributarySlots)
: m_serviceType(serviceType),
  m_tributarySlots(tributarySlots)
{}

ServiceType LabelOTNImpl::getServiceType() const
{
  return m_serviceType;
}

auto LabelOTNImpl::getTributarySlots() const -> TributarySlotsResult
{
  return m_tributarySlots;
}

auto LabelOTNImpl::getFrequencyInterval() const -> FrequencyIntervalResult
{
  return
    FrequencyIntervalResult{label::ErrorCode::not_layer_0};
}

bool LabelOTNImpl::encode(ProtocolBuffer&  buffer)
{
  return true;
}

bool LabelOTNImpl::encode(Persistency&     persistency)
{
  return true;
}

}; // namespace label::impl