#ifndef LIBS_IPCC_STATE_HPP_
#define LIBS_IPCC_STATE_HPP_
/*
 * IPCC_State.hpp
 *
 *  Created on: 11.03.2015
 *      Author: tom
 */

#include <iostream>

namespace lmp
{
  namespace cc
  {
    namespace appl
    {
      class State
      {
      public:
        enum Type
        {
          Down,
          ConfSnd,
          ConfRcv,
          Active,
          Up,
          GoingDown
        };
        inline std::ostream& print(std::ostream& os) const
        { return do_print(os); }
        inline Type getType() const { return do_getType(); }
        inline bool operator==(const State& other) const { return getType() == other.getType(); }
        inline bool operator!=(const State& other) const { return getType() != other.getType(); }
        virtual ~State(){}
      private:
        virtual std::ostream& do_print(std::ostream& os) const = 0;
        virtual Type do_getType() const = 0;
      };
      inline std::ostream& operator<<(
        std::ostream&       os,
        const State&        state)
      { return state.print(os); }
      std::ostream& operator<<(
        std::ostream&       os,
        State::Type         stType);

      template <State::Type  stateType>
      class StateTag : public State
      {
      public:
        virtual ~StateTag(){}
        StateTag(){}
      private:
        virtual std::ostream& do_print(std::ostream& os) const
        { os << getType(); return os; }
        virtual State::Type do_getType() const { return stateType; }
      };
      typedef StateTag<State::Down>       Down;
      typedef StateTag<State::ConfSnd>    ConfSnd;
      typedef StateTag<State::ConfRcv>    ConfRcv;
      typedef StateTag<State::Active>     Active;
      typedef StateTag<State::Up>         Up;
      typedef StateTag<State::GoingDown>  GoingDown;
    } // namespace appl
  } // namespace cc
} // namespace lmp


#endif /* LIBS_IPCC_STATE_HPP_ */
