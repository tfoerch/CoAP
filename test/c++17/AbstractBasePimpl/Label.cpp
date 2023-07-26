#include "Label.hpp"
#include "LabelOTNImpl.hpp"
#include "LabelOCHImpl.hpp"

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


