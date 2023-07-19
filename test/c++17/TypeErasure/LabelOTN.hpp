#ifndef LABEL_OTN_HPP
#define LABEL_OTN_HPP

#include "LabelTypes.hpp"

class MsgBuffer;

namespace label
{
  class LabelOTN
  {
  public:
    LabelOTN(ServiceType serviceType, const TributarySlots& tributarySlots);
    LabelOTN(ServiceType serviceType, TributarySlots&& tributarySlots);
    ServiceType getServiceType() const;
    TributarySlotsResult getTributarySlots() const;
    FrequencyIntervalResult getFrequencyInterval() const;
    void encode(MsgBuffer&  buffer) const;
  private:
    ServiceType     m_serviceType;
    TributarySlots  m_tributarySlots;
  };
}; // namespace label

#endif /* LABEL_OTN_HPP */
