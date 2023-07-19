#ifndef LABEL_OTN_IMPL_HPP
#define LABEL_OTN_IMPL_HPP

#include "LabelIF.hpp"

class LabelOTNImpl : public LabelIF
{
public:
  LabelOTNImpl(ServiceType serviceType, const TributarySlots& tributarySlots);
  LabelOTNImpl(ServiceType serviceType, TributarySlots&& tributarySlots);
  ServiceType getServiceType() const override;
  TributarySlotsResult getTributarySlots() const override;
  FrequencyIntervalResult getFrequencyInterval() const override;
  bool encode(ProtocolBuffer&  buffer) override;
  bool encode(Persistency&     persistency) override;
private:
  ServiceType     m_serviceType;
  TributarySlots  m_tributarySlots;
};

#endif /* LABEL_OTN_IMPL_HPP */
