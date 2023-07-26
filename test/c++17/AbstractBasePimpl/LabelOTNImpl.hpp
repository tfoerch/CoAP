#ifndef LABEL_OTN_IMPL_HPP
#define LABEL_OTN_IMPL_HPP

#include "LabelImplBase.hpp"

namespace label::impl
{
  class LabelOTNImpl : public LabelImplBase
  {
  public:
    LabelOTNImpl(ServiceType serviceType, const TributarySlots& tributarySlots);
    LabelOTNImpl(ServiceType serviceType, TributarySlots&& tributarySlots);
    ServiceType getServiceType() const override;
    TributarySlotsResult getTributarySlots() const override;
    FrequencyIntervalResult getFrequencyInterval() const override;
    bool encode(MsgBuffer&  buffer) override;
  private:
    ServiceType     m_serviceType;
    TributarySlots  m_tributarySlots;
  };
}; // namespace label::impl

#endif /* LABEL_OTN_IMPL_HPP */
