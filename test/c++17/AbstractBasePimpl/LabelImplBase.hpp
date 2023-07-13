#ifndef LABEL_IMPL_BASE_HPP
#define LABEL_IMPL_BASE_HPP

#include "Label.hpp"

namespace label::impl
{
  class LabelImplBase
  {
  public:
    using TributarySlots = label::TributarySlots;
    using FrequencyInterval = label::FrequencyInterval;
    using TributarySlotsResult = label::TributarySlotsResult;
    using FrequencyIntervalResult = label::FrequencyIntervalResult;
    virtual ~LabelImplBase() = default;
    virtual ServiceType getServiceType() const = 0;
    virtual TributarySlotsResult getTributarySlots() const = 0; // layer 1
    virtual FrequencyIntervalResult getFrequencyInterval() const = 0;// layer 0
    virtual bool encode(ProtocolBuffer&  buffer) = 0;
    virtual bool encode(Persistency&     persistency) = 0;
  };
}; // namespace label::impl


#endif /* LABEL_IMPL_BASE_HPP */
