#include "LabelOCH.hpp"

namespace label
{

LabelOCH::LabelOCH(const FrequencyInterval& frequencyInterval)
: m_frequencyInterval(frequencyInterval)
{}

LabelOCH::LabelOCH(FrequencyInterval&& frequencyInterval)
: m_frequencyInterval(frequencyInterval)
{}

ServiceType LabelOCH::getServiceType() const
{
  return ServiceType::och;
}

auto LabelOCH::getFrequencyInterval() const -> FrequencyIntervalResult
{
  return m_frequencyInterval;
}

void LabelOCH::encode(MsgBuffer&  /*buffer*/) const
{
}

}; // namespace label
