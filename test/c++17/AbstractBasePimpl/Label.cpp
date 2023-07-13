#include "Label.hpp"
#include "LabelOTNImpl.hpp"
#include "LabelOCHImpl.hpp"

#include <vector>

Label::~Label() = default; // std::unique_ptr requires declaration of LabelImplBase to call delete

Label::Label(ServiceType serviceType, const TributarySlots& tributarySlots)
: m_labelImplPtr(std::make_unique<label::impl::LabelOTNImpl>(serviceType, tributarySlots))
{
}

Label::Label(ServiceType serviceType, TributarySlots&& tributarySlots)
: m_labelImplPtr(std::make_unique<label::impl::LabelOTNImpl>(serviceType, tributarySlots))
{
}

Label::Label(const FrequencyInterval& frequencyInterval)
: m_labelImplPtr(std::make_unique<label::impl::LabelOCHImpl>(frequencyInterval))
{}

Label::Label(FrequencyInterval&& frequencyInterval)
: m_labelImplPtr(std::make_unique<label::impl::LabelOCHImpl>(frequencyInterval))
{}

ServiceType Label::getServiceType() const
{
  return
    ( m_labelImplPtr ?
      m_labelImplPtr->getServiceType() :
      ServiceType::undef );
}

auto Label::getTributarySlots() const -> TributarySlotsResult
{
  return
    ( m_labelImplPtr ?
      m_labelImplPtr->getTributarySlots() :
      TributarySlotsResult{label::ErrorCode::not_layer_1} );
}

auto Label::getFrequencyInterval() const -> FrequencyIntervalResult
{
  return
    ( m_labelImplPtr ?
      m_labelImplPtr->getFrequencyInterval() :
      FrequencyIntervalResult{label::ErrorCode::not_layer_0} );
}

//bool Label::encode(ProtocolBuffer&  buffer);
//bool Label::encode(Persistency&     persistency);
//Label Label::decode(const ProtocolBuffer&  buffer);
//Label Label::decode(const Persistency&     persistency);

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

