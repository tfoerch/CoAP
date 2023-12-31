#include "LabelOCHImpl.hpp"
#include "LabelOTNImpl.hpp"

#include <cstddef> // std::size_t
#include <cassert>
#include <algorithm>
#include <functional>
#include <vector>
#include <iterator>
#include <iostream>

struct IsNotLayer0Ftor
{
  bool operator()(const LabelIF& label) const
  { return label.getServiceType() != ServiceType_och; }
};
struct IsNotLayer1Ftor
{
  bool operator()(const LabelIF& label) const
  { return
      ( label.getServiceType() != ServiceType_odu0 &&
        label.getServiceType() != ServiceType_odu2e ); }
};

int main()
{
  // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
  const uint32_t tribSlotsOf1stOdukLabel[] = { 1 };
  const uint32_t tribSlotsOf2ndOdukLabel[] = { 4, 5, 6, 7, 12, 13, 14, 15 }; // ordered for easier tests
  const uint32_t tribSlotsOf3rdOdukLabel[] = { 8 };
  const label::FrequencySlot freqSlotOf1stOchLabel(-32, 4);
  const label::FrequencySlot freqSlotOf2ndOchLabel(-4, 4);
  // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
  std::vector<LabelIF::LabelIFPtr>  layer0Labels;
  std::vector<LabelIF::LabelIFPtr>  layer1Labels;

  const LabelOTNImpl  odu0Label(ServiceType_odu0, label::TributarySlots(tribSlotsOf1stOdukLabel, tribSlotsOf1stOdukLabel + sizeof(tribSlotsOf1stOdukLabel)/sizeof(uint32_t)));
  const LabelOTNImpl  odu2eLabel(ServiceType_odu2e, label::TributarySlots(tribSlotsOf2ndOdukLabel, tribSlotsOf2ndOdukLabel + sizeof(tribSlotsOf2ndOdukLabel)/sizeof(uint32_t)));
  const LabelOCHImpl  ochLabel(freqSlotOf1stOchLabel);
  // Label copy1OfOdu0Label = odu0Label; error deleted copy ctor
  // Label copy1OfOdu0Label; copy1OfOdu0Label = odu0Label; error deleted assign
  std::vector<LabelIF::LabelIFPtr>  labels;
//  labels.emplace_back(ServiceType_odu0, label::TributarySlots({ 23 }));  // construct the Label in-place
//  labels.emplace_back(label::FrequencySlot{-4, 4}); // construct the Label in-place
  labels.push_back(new LabelOTNImpl(ServiceType_odu0, label::TributarySlots(tribSlotsOf3rdOdukLabel, tribSlotsOf3rdOdukLabel + sizeof(tribSlotsOf3rdOdukLabel)/sizeof(uint32_t))));
  labels.push_back(new LabelOCHImpl(freqSlotOf2ndOchLabel)); // constructed then moved
  // std::vector<Label>  copyofLabels; copyofLabels = labels; error deleted assign
}
