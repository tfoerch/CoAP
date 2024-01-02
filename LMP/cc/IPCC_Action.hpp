#ifndef LIBS_IPCC_ACTION_HPP_
#define LIBS_IPCC_ACTION_HPP_
/*
 * IPCC_Action.hpp
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
      class Action
      {
      public:
        enum ActionType
        {
          ActionSendConfig,
          ActionStopSendConfig,
          ActionResendConfig,
          ActionSendConfigAck,
          ActionSendConfigNack,
          ActionSendHello,
          ActionStopSendHello,
          ActionSetCCDownFlag,
          ActionClearCCDownFlag,
          ActionNoAction
        };
        inline std::ostream& print(std::ostream& os) const
        { return do_print(os); }
        inline ActionType getType() const { return do_getType(); }
        virtual ~Action(){}
      private:
        virtual std::ostream& do_print(std::ostream& os) const = 0;
        virtual ActionType do_getType() const = 0;
      };
      inline std::ostream& operator<<(
        std::ostream&       os,
        const Action&       action)
      { return action.print(os); }
      std::ostream& operator<<(
        std::ostream&       os,
        Action::ActionType  actionType);

      template <Action::ActionType  actionType>
      class ActionTag : public Action
      {
      public:
        virtual ~ActionTag(){}
      private:
        virtual std::ostream& do_print(std::ostream& os) const
        { os << getType(); return os; }
        virtual Action::ActionType do_getType() const { return actionType; };
      };
    } // namespace appl
  } // namespace cc
} // namespace lmp


#endif /* LIBS_IPCC_ACTION_HPP_ */
