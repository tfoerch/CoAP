#ifndef LABEL_CONCEPT_HPP
#define LABEL_CONCEPT_HPP

#include "LabelTypes.hpp"

class MsgBuffer;

namespace label::impl
{
  class LabelConcept
  {
  public:
    using TributarySlots = label::TributarySlots;
    using FrequencyInterval = label::FrequencyInterval;
    using TributarySlotsResult = label::TributarySlotsResult;
    using FrequencyIntervalResult = label::FrequencyIntervalResult;
    virtual ~LabelConcept() = default;
    virtual LabelPtr clone() const = 0;
    virtual ServiceType getServiceType() const = 0;
    virtual TributarySlotsResult getTributarySlots() const = 0; // layer 1
    virtual FrequencyIntervalResult getFrequencyInterval() const = 0;// layer 0
    virtual void encode(MsgBuffer&  buffer) const = 0;
  };
}; // namespace label::impl

#endif /* LABEL_CONCEPT_HPP */
