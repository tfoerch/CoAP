#ifndef LABEL_HPP
#define LABEL_HPP

#include "LabelTypes.hpp"
#include "LabelModel.hpp"

class MsgBuffer;

class Label
{
public:
  using TributarySlots = label::TributarySlots;
  using FrequencyInterval = label::FrequencyInterval;
  using TributarySlotsResult = label::TributarySlotsResult;
  using FrequencyIntervalResult = label::FrequencyIntervalResult;
  Label(const Label&  label)
  : m_labelPtr(label.m_labelPtr ?
               label.m_labelPtr->clone() :
               LabelPtr())
  {}
  Label(Label&&  label) = default;
  template <NotOfTypeLabel T>
  explicit Label(T&& label)
  : m_labelPtr(std::make_unique<label::impl::LabelModel<T>>(std::forward<T>(label)))
  {}
  Label& operator=(const Label&  label)
  { Label tmp(label); m_labelPtr = std::move(tmp.m_labelPtr);
    return *this; }
  Label& operator=(Label&&  label) = default;
  ~Label() = default;
  ServiceType getServiceType() const
  { return
      ( m_labelPtr ?
        m_labelPtr->getServiceType() :
        ServiceType::undef ); }
  TributarySlotsResult getTributarySlots() const // layer 1
  { return
      ( m_labelPtr ?
        m_labelPtr->getTributarySlots() :
        TributarySlotsResult{label::ErrorCode::not_layer_1} ); }
  FrequencyIntervalResult getFrequencyInterval() const// layer 0
  { return
      ( m_labelPtr ?
        m_labelPtr->getFrequencyInterval() :
        FrequencyIntervalResult{label::ErrorCode::not_layer_0} ); }
  void encode(MsgBuffer&  buffer) const
  {
    if (m_labelPtr)
    {
      m_labelPtr->encode(buffer);
    }
  }
//  static Label decode(const MsgBuffer&  buffer);
private:
  using LabelPtr = label::impl::LabelPtr;
  LabelPtr  m_labelPtr;
};

#endif /* LABEL_HPP */
