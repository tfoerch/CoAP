#ifndef LABEL_OCH_HPP
#define LABEL_OCH_HPP

#include "LabelTypes.hpp"

class MsgBuffer;

namespace label
{
  class LabelOCH
  {
  public:
    explicit LabelOCH(const FrequencyInterval& frequencyInterval);
    explicit LabelOCH(FrequencyInterval&& frequencyInterval);
    ServiceType getServiceType() const;
    FrequencyIntervalResult getFrequencyInterval() const;
    void encode(MsgBuffer&  buffer) const;
  private:
    FrequencyInterval  m_frequencyInterval;
  };
}; // namespace label

#endif /* LABEL_OCH_HPP */
