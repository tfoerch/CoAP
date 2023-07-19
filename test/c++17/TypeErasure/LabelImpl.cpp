#include "LabelImpl.hpp"
#include "LabelOTN.hpp"
#include "LabelOCH.hpp"

namespace label::impl
{
  ServiceType  getServiceType(const LabelOTN& label)
  { return label.getServiceType(); }
  ServiceType  getServiceType(const LabelOCH& label)
  { return label.getServiceType(); }

  label::TributarySlotsResult getTributarySlots(const LabelOTN& label)
  { return label.getTributarySlots(); }
  label::TributarySlotsResult getTributarySlots(const LabelOCH& label)
  { return label::TributarySlotsResult{label::ErrorCode::not_layer_1}; }

  label::FrequencyIntervalResult getFrequencyInterval(const LabelOTN& label)
  { return label::FrequencyIntervalResult{label::ErrorCode::not_layer_0}; }
  label::FrequencyIntervalResult getFrequencyInterval(const LabelOCH& label)
  { return label.getFrequencyInterval(); }

  void encode(const LabelOTN& label, MsgBuffer&  buffer)
  { label.encode(buffer); }
  void encode(const LabelOCH& label, MsgBuffer&  buffer)
  { label.encode(buffer); }

}; // namespace label::impl
