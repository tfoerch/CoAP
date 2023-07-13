#ifndef LABEL_HPP
#define LABEL_HPP

#include <memory> // std::unique_ptr
#include <cstdint> // std::uint32_t and std::int32_t
#include <utility> // std::pair
#include <set> // std::set
#include <variant> // std::variant

class ProtocolBuffer;
class Persistency;

enum class ServiceType { och, odu0, odu2e, undef };

namespace label
{
  using TributarySlots = std::set<std::uint32_t>; // layer 1
  using FrequencyInterval =
    std::pair<std::int32_t /* lower bound */,
              std::int32_t /* upper bound */>; // layer 0
  enum class ErrorCode { not_layer_1, not_layer_0 };
  using TributarySlotsResult = std::variant<TributarySlots, ErrorCode>;
  using FrequencyIntervalResult = std::variant<FrequencyInterval, ErrorCode>;
  namespace impl
  {
    class LabelImplBase;
  };
};

class Label
{
public:
  using TributarySlots = label::TributarySlots;
  using FrequencyInterval = label::FrequencyInterval;
  using TributarySlotsResult = label::TributarySlotsResult;
  using FrequencyIntervalResult = label::FrequencyIntervalResult;
  Label(ServiceType serviceType, const TributarySlots& tributarySlots);
  Label(ServiceType serviceType, TributarySlots&& tributarySlots);
  explicit Label(const FrequencyInterval& frequencyInterval);
  explicit Label(FrequencyInterval&& frequencyInterval);
  Label() = default;
  Label(const Label&) = delete; // implicitly deleted due to deleted copy ctor of std::unique_ptr
  Label(Label&&) = default;
  Label& operator=(const Label&) = delete; // implicitly deleted
  Label& operator=(Label&&) = default;
  ~Label();
  ServiceType getServiceType() const;
  TributarySlotsResult getTributarySlots() const; // layer 1
  FrequencyIntervalResult getFrequencyInterval() const;// layer 0
  bool encode(ProtocolBuffer&  buffer);
  bool encode(Persistency&     persistency);
  static Label decode(const ProtocolBuffer&  buffer);
  static Label decode(const Persistency&     persistency);
private:
  std::unique_ptr<label::impl::LabelImplBase>  m_labelImplPtr;
};
#endif /* LABEL_HPP */
