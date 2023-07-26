#include "Label.hpp"

#include <vector>

int main()
{
  Label  odu0Label(ServiceType::odu0, label::TributarySlots({ 1 }));
  Label  odu2eLabel(ServiceType::odu2e, label::TributarySlots({ 4, 5, 6, 7, 12, 13, 14, 15 }));
  Label  ochLabel(label::FrequencyInterval{-32, -24});
  // Label copy1OfOdu0Label = odu0Label; error deleted copy ctor
  // Label copy1OfOdu0Label; copy1OfOdu0Label = odu0Label; error deleted assign
  std::vector<Label>  labels;
  labels.emplace_back(ServiceType::odu0, label::TributarySlots({ 23 })); // construct the Label in-place
  labels.emplace_back(label::FrequencyInterval{-4, +4}); // construct the Label in-place
  labels.push_back(Label(ServiceType::odu0, label::TributarySlots({ 23 }))); // constructed then moved
  labels.push_back(Label(label::FrequencyInterval{-4, +4})); // constructed then moved
  // std::vector<Label>  copyofLabels; copyofLabels = labels; error deleted assign
}
