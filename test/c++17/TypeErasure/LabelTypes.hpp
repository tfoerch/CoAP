#ifndef LABEL_TYPES_HPP
#define LABEL_TYPES_HPP

#include <memory> // std::unique_ptr
#include <cstdint> // std::uint32_t and std::int32_t
#include <utility> // std::pair
#include <set> // std::set
#include <variant> // std::variant
#include <concepts>

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
    class LabelConcept;
    using LabelPtr = std::unique_ptr<LabelConcept>;
  };
};

class Label;

template <typename T>
concept NotOfTypeLabel =
   ( !std::same_as<std::decay_t<T>, Label> &&
     !std::derived_from<std::decay_t<T>, Label> );

#endif /* LABEL_TYPES_HPP */
