#ifndef FSM_HPP_
#define FSM_HPP_
/*
 * FSM.hpp
 *
 *  Created on: 27.02.2022
 *      Author: tom
 */
#include <type_traits>
#include <utility>

namespace fsm
{
  template <class...>
  struct type {};
  template <class...>
  struct type_list {
    using type = type_list;
  };
  template <class... Ts>
  struct inherit : Ts... {
    using type = inherit;
  };
  template <class, class...>
  struct unique_impl;
  template <class T, class... Rs, class... Ts>
  struct unique_impl<type<Rs...>, T, Ts...> : std::conditional_t<std::is_base_of<type<T>, inherit<type<Rs>...>>::value,
                                                                 unique_impl<type<Rs...>, Ts...>,
                                                                 unique_impl<type<Rs..., T>, Ts...>>
  {};
  template <class... Rs>
  struct unique_impl<type<Rs...>> : type_list<Rs...> {};
  template <class... Ts>
  struct unique : unique_impl<type<>, Ts...> {};
  template <class T>
  struct unique<T> : type_list<T> {};
  template <class... Ts>
  using unique_t = typename unique<Ts...>::type;

  template <typename...>
  struct transition;

  template <class>
  struct state;
  template <class>
  struct event;

  template <class TState>
  struct state_impl
  {
    template <class E>
    auto operator+(const E& e) const
    {
      return transition<TState, event<E>>{static_cast<const TState &>(*this), e};
    }
  };

  template <class TState>
  struct state : state_impl<state<TState>>
  {
    using type = TState;
  #if 0
    template <class T>
    auto operator=(const T &t) const {
      return transition<T, state>{t, *this};
    }
  #endif
  };

  template <class TEvent>
  struct event
  {
  #if 0
    template <typename Fn, typename... Args, std::predicate<Fn, Args...> Predicate>
    auto operator[](const Predicate& t) const {
      return transition_eg<event, std::reference_wrapper<const Predicate> >{*this, std::cref(t)};
    }
    template <typename Fn, typename... Args, std::invocable<Fn, Args...> Invocable>
    auto operator/(const Invocable &t) const {
      return transition_ea<event, std::reference_wrapper<Invocable>>{*this, std::ref(t)};
    }
  #endif
    auto operator()() const { return TEvent{}; }
  };

  template <class S2, class E>
  struct transition<state<S2>, event<E>>
  {
    template <class S1>
    auto operator=(const S1&) const
    {
      return transition<state<S1>, state<S2>, event<E>>{};
    }
    const state<S2>& s2;
    event<E> e;
  };

  template <class S1, class S2, class E>
  struct transition<state<S1>, state<S2>, event<E>>
  {
  //  static constexpr auto initial = state<S2>::initial;
    using src_state = typename state<S2>::type;
    using dst_state = typename state<S1>::type;
    using event = E;
  };


} // namespace fsm

#endif /* FSM_HPP_ */
