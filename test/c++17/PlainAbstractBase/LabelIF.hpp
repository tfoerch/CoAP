#ifndef LABELIF_HPP
#define LABELIF_HPP

#include <memory> // std::unique_ptr
#include <cstdint> // std::uint32_t and std::int32_t
#include <utility> // std::pair
#include <set> // std::set
#include <variant> // std::variant

class ProtocolBuffer;
class Persistency;

enum class ServiceType { och, odu0, odu2e, undef };

class LabelIF;

namespace label
{
  using TributarySlots = std::set<std::uint32_t>; // layer 1
  using FrequencyInterval =
    std::pair<std::int32_t /* lower bound */,
              std::int32_t /* upper bound */>; // layer 0
  enum class ErrorCode { not_layer_1, not_layer_0 };
  using TributarySlotsResult = std::variant<TributarySlots, ErrorCode>;
  using FrequencyIntervalResult = std::variant<FrequencyInterval, ErrorCode>;
  using LabelIFPtr = std::unique_ptr<LabelIF>;
};

class LabelIF
{
public:
  using TributarySlots = label::TributarySlots;
  using FrequencyInterval = label::FrequencyInterval;
  using TributarySlotsResult = label::TributarySlotsResult;
  using FrequencyIntervalResult = label::FrequencyIntervalResult;
  virtual ~LabelIF() = default;
  virtual ServiceType getServiceType() const = 0;
  virtual TributarySlotsResult getTributarySlots() const = 0; // layer 1
  virtual FrequencyIntervalResult getFrequencyInterval() const = 0;// layer 0
  virtual bool encode(ProtocolBuffer&  buffer) = 0;
  virtual bool encode(Persistency&     persistency) = 0;
};

#endif /* LABELIF_HPP */
