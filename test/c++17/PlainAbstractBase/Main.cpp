#include "LabelOCHImpl.hpp"
#include "LabelOTNImpl.hpp"

#include <vector>

auto main() -> int
{
  const LabelOTNImpl  odu0Label(ServiceType::odu0, label::TributarySlots({ 1 }));
  const LabelOTNImpl  odu2eLabel(ServiceType::odu2e, label::TributarySlots({ 4, 5, 6, 7, 12, 13, 14, 15 })); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
  const LabelOCHImpl  ochLabel(label::FrequencySlot{-32, 4});
  // Label copy1OfOdu0Label = odu0Label; error deleted copy ctor
  // Label copy1OfOdu0Label; copy1OfOdu0Label = odu0Label; error deleted assign
  std::vector<label::LabelIFPtr>  labels;
//  labels.emplace_back(ServiceType::odu0, label::TributarySlots({ 23 }));  // construct the Label in-place
//  labels.emplace_back(label::FrequencySlot{-4, 4}); // construct the Label in-place
  labels.push_back(std::make_unique<LabelOTNImpl>(ServiceType::odu0, label::TributarySlots({ 23 }))); // NOLINT(cppcoreguidelines-avoid-magic-numbers) constructed then moved
  labels.push_back(std::make_unique<LabelOCHImpl>(label::FrequencySlot{-4, 4})); // constructed then moved
  // std::vector<Label>  copyofLabels; copyofLabels = labels; error deleted assign
}
