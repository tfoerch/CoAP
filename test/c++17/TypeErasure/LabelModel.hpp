#ifndef LABEL_MODEL_HPP
#define LABEL_MODEL_HPP

#include "LabelConcept.hpp"
#include "LabelImpl.hpp"

namespace label::impl
{
#if __cpp_concepts
  template <NotOfTypeLabel T>
#else
  template <typename T>
#endif // __cpp_concepts
  class LabelModel final : public LabelConcept
  {
  public:
    LabelModel(T&&  label)
    : m_label(std::forward<T>(label))
    {}
    LabelPtr clone() const override
    {
      return
        std::make_unique<LabelModel>(*this);
    }
    ServiceType getServiceType() const override
    {
      return
        label::impl::getServiceType(m_label);
    }
    TributarySlotsResult getTributarySlots() const override // layer 1
    {
      return
        label::impl::getTributarySlots(m_label);
    }
    FrequencyIntervalResult getFrequencyInterval() const override // layer 0
    {
      return
        label::impl::getFrequencyInterval(m_label);
    }
    void encode(MsgBuffer&  buffer) const override
    {
      label::impl::encode(m_label, buffer);
    }
  private:
     T  m_label;
  };
}; // namespace label::impl

#endif /* LABEL_MODEL_HPP */
