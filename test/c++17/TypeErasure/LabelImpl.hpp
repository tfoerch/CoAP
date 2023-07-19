#ifndef LABEL_IMPL_HPP
#define LABEL_IMPL_HPP

#include "LabelTypes.hpp"

class MsgBuffer;

namespace label
{
  class LabelOTN;
  class LabelOCH;

  namespace impl
  {
    ServiceType  getServiceType(const LabelOTN& label);
    ServiceType  getServiceType(const LabelOCH& label);

    label::TributarySlotsResult getTributarySlots(const LabelOTN& label);
    label::TributarySlotsResult getTributarySlots(const LabelOCH& label);

    label::FrequencyIntervalResult getFrequencyInterval(const LabelOTN& label);
    label::FrequencyIntervalResult getFrequencyInterval(const LabelOCH& label);

    void encode(const LabelOTN& label, MsgBuffer&  buffer);
    void encode(const LabelOCH& label, MsgBuffer&  buffer);
  }; // namespace impl
}; // namespace label

#endif /* LABEL_IMPL_HPP */
