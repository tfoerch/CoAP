#include "LabelOCHImpl.hpp"

namespace label::impl
{

LabelOCHImpl::LabelOCHImpl(const FrequencyInterval& frequencyInterval)
: m_frequencyInterval(frequencyInterval)
{}

LabelOCHImpl::LabelOCHImpl(FrequencyInterval&& frequencyInterval)
: m_frequencyInterval(frequencyInterval)
{}

ServiceType LabelOCHImpl::getServiceType() const
{
  return ServiceType::och;
}

auto LabelOCHImpl::getTributarySlots() const -> TributarySlotsResult
{
  return
    TributarySlotsResult{label::ErrorCode::not_layer_1};
}

auto LabelOCHImpl::getFrequencyInterval() const -> FrequencyIntervalResult
{
  return m_frequencyInterval;
}

bool LabelOCHImpl::encode(MsgBuffer&  /*buffer*/)
{
  return true;
}

}; // namespace label::impl
