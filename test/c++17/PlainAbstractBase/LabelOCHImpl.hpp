#ifndef LABEL_OCH_IMPL_HPP
#define LABEL_OCH_IMPL_HPP

#include "LabelIF.hpp"

class LabelOCHImpl : public LabelIF
{
public:
  explicit LabelOCHImpl(const FrequencyInterval& frequencyInterval);
  explicit LabelOCHImpl(FrequencyInterval&& frequencyInterval);
  ServiceType getServiceType() const override;
  TributarySlotsResult getTributarySlots() const override;
  FrequencyIntervalResult getFrequencyInterval() const override;
  bool encode(MsgBuffer&  buffer) override;
private:
  FrequencyInterval  m_frequencyInterval;
};

#endif /* LABEL_OCH_IMPL_HPP */
