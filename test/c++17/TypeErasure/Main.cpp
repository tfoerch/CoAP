#include "Label.hpp"
#include "LabelOTN.hpp"
#include "LabelOCH.hpp"

#include <vector>
#include <cassert>

int main()
{
  static_assert(std::is_same_v<std::decay_t<Label&>, Label>);
#if __cpp_concepts
  static_assert(NotOfTypeLabel<label::LabelOTN>);
#else
  static_assert(notOfTypeLabel<label::LabelOTN>());
#endif // __cpp_concepts
  Label  odu0Label(label::LabelOTN(ServiceType::odu0, label::TributarySlots({ 1 })));
  assert(odu0Label.getServiceType() == ServiceType::odu0);
  Label  odu2eLabel(label::LabelOTN(ServiceType::odu2e, label::TributarySlots({ 4, 5, 6, 7, 12, 13, 14, 15 })));
  Label  ochLabel(label::LabelOCH(label::FrequencyInterval{-32, -24}));
  Label copy1OfOdu0Label = odu0Label;
  std::vector<Label>  labels;
  labels.emplace_back(label::LabelOTN(ServiceType::odu0, label::TributarySlots({ 23 }))); // construct the Label in-place
  labels.emplace_back(label::LabelOCH(label::FrequencyInterval{-4, +4})); // construct the Label in-place
  labels.push_back(Label(label::LabelOTN(ServiceType::odu0, label::TributarySlots({ 23 })))); // constructed then moved
  labels.push_back(Label(label::LabelOCH(label::FrequencyInterval{-4, +4}))); // constructed then moved
  std::vector<Label>  copyofLabels; copyofLabels = labels;
}
