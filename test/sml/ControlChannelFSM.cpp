#include <boost/sml.hpp>
#include <cassert>
#include <iostream>

namespace sml = boost::sml;

//                          +--------+
//       +----------------->|        |<--------------+
//       |       +--------->|  Down  |<----------+   |
//       |       |+---------|        |<-------+  |   |
//       |       ||         +--------+        |  |   |
//       |       ||           |    ^       2,9| 2|  2|
//       |       ||1b       1a|    |          |  |   |
//       |       ||           v    |2,9       |  |   |
//       |       ||         +--------+        |  |   |
//       |       ||      +->|        |<------+|  |   |
//       |       ||  4,7,|  |ConfSnd |       ||  |   |
//       |       || 14,15+--|        |<----+ ||  |   |
//       |       ||         +--------+     | ||  |   |
//       |       ||       3,8a| |          | ||  |   |
//       |       || +---------+ |8b  14,12a| ||  |   |
//       |       || |           v          | ||  |   |
//       |       |+-|------>+--------+     | ||  |   |
//       |       |  |    +->|        |-----|-|+  |   |
//       |       |  |6,14|  |ConfRcv |     | |   |   |
//       |       |  |    +--|        |<--+ | |   |   |
//       |       |  |       +--------+   | | |   |   |
//       |       |  |          5| ^      | | |   |   |
//       |       |  +---------+ | |      | | |   |   |
//       |       |            | | |      | | |   |   |
//       |       |            v v |6,12b | | |   |   |
//       |       |10        +--------+   | | |   |   |
//       |       +----------|        |   | | |   |   |
//       |       |       +--| Active |---|-+ |   |   |
//  10,17|       |   5,16|  |        |-------|---+   |
//   +-------+ 9 |   13  +->|        |   |   |       |
//   | Going |<--|----------+--------+   |   |       |
//   | Down  |   |           11| ^       |   |       |
//   +-------+   |             | |5      |   |       |
//       ^       |             v |  6,12b|   |       |
//       |9      |10        +--------+   |   |12a,14 |
//       |       +----------|        |---+   |       |
//       |                  |   Up   |-------+       |
//       +------------------|        |---------------+
//                          +--------+
//                            |   ^
//                            |   |
//                            +---+
//                           11,13,16

namespace cc
{
  struct ConfigMsg
  {
    bool validConfig = true;
  };
  struct ConfigNackMsg {};

  struct HelloMsg {};

  // events
  struct EvBringUp {};
  struct EvCCDn {};
  struct EvConfDone {};
  struct EvConfErr
  {
    EvConfErr(const ConfigNackMsg& configNackMsg) : m_configNackMsg(configNackMsg) {}
    const ConfigNackMsg& m_configNackMsg;
  };
  struct EvNewConfOK {};
  struct EvNewConfErr {};
  struct EvContenWin {};
  struct EvContenLost
  {
    EvContenLost(const ConfigMsg& configMsg) : m_configMsg(configMsg) {}
    const ConfigMsg& m_configMsg;
  };
  struct EvAdminDown {};
  struct EvNbrGoesDn {};
  struct EvHelloRcvd {};
  struct EvHoldTimer {};
  struct EvSeqNumErr {};
  struct EvReconfig {};
  struct EvConfRet {};
  struct EvHelloRet {};
  struct EvDownTimer {};

  struct ActionSendConfig {};
  struct ActionStopSendConfig {};
  struct ActionResendConfig {};
  struct ActionSendConfigAck {};
  struct ActionSendConfigNack {};
  struct ActionSendHello {};
  struct ActionStopSendHello {};
  struct ActionSetCCDownFlag {};
  struct ActionClearCCDownFlag {};
  struct ActionNoAction {};

  // states
  struct Down {};
  struct ConfSnd {};
  struct ConfRcv {};
  struct Active {};
  struct Up {};
  struct GoingDown {};
  auto down = sml::state<Down>;
  auto confSnd = sml::state<ConfSnd>;
  auto confRcv = sml::state<ConfRcv>;
  auto active = sml::state<Active>;
  auto up = sml::state<Up>;
  auto goingDown = sml::state<GoingDown>;

  struct ControlChannelFSM;

  struct ActiveConfig
  {
    template <class TEvent>
    bool operator()(ControlChannelFSM&, const TEvent&) const;
  } activeConfig;

  struct PassiveConfig
  {
    template <class TEvent>
    bool operator()(const ControlChannelFSM&, const TEvent&) const;
  } passiveConfig;

  struct NotAcceptableConfig
  {
    template <class TEvent>
    bool operator()(const ControlChannelFSM&, const TEvent&) const;
  } notAcceptableConfig;

  struct AcceptableConfig
  {
    template <class TEvent>
    bool operator()(const ControlChannelFSM&, const TEvent&) const;
  } acceptableConfig;

  struct SendConfig
  {
    template <class TEvent>
    void operator()(ControlChannelFSM&, const TEvent&);
  } sendConfig;

  struct StopSendConfig
  {
    template <class TEvent>
    void operator()(ControlChannelFSM&, const TEvent&);
  } stopSendConfig;

  struct ResendConfig
  {
    template <class TEvent>
    void operator()(ControlChannelFSM&, const TEvent&);
  } resendConfig;

  struct SendConfigNack
  {
    template <class TEvent>
    void operator()(ControlChannelFSM&, const TEvent&);
  } sendConfigNack;

  struct SendConfigAck
  {
    template <class TEvent>
    void operator()(ControlChannelFSM&, const TEvent&);
  } sendConfigAck;

  struct SendHello
  {
    template <class TEvent>
    void operator()(ControlChannelFSM&, const TEvent&);
  } sendHello;

  struct StopSendHello
  {
    template <class TEvent>
    void operator()(ControlChannelFSM&, const TEvent&);
  } stopSendHello;

  struct SetCCDownFlag
  {
    template <class TEvent>
    void operator()(ControlChannelFSM&, const TEvent&);
  } setCCDownFlag;

  struct ControlChannelFSM
  {
  public:
    auto operator()() const
    {
      using namespace sml;
      // clang-format off
      return make_transition_table(
        *down     + event<EvBringUp> [ activeConfig ]           / sendConfig     = confSnd,
        down      + event<EvBringUp> [ passiveConfig ]                           = confRcv,
        confSnd   + sml::on_entry<_>                            / sendConfig,
        confSnd   + sml::on_exit<_>                             / stopSendConfig,
        confSnd   + event<EvCCDn>                               / stopSendConfig = down,
        confSnd   + event<EvAdminDown>                          / stopSendConfig = down,
        confSnd   + event<EvConfErr>                            / sendConfig     = confSnd,
        confSnd   + event<EvContenWin>                                           = confSnd,
        confSnd   + event<EvReconfig>                           / sendConfig     = confSnd,
        confSnd   + event<EvConfRet>                            / resendConfig   = confSnd,
        confSnd   + event<EvContenLost> [ notAcceptableConfig ] / stopSendConfig = confRcv,
        confSnd   + event<EvConfDone>                           / stopSendConfig = active,
        confSnd   + event<EvContenLost> [ acceptableConfig ]    / stopSendConfig = active,
        confRcv   + event<EvCCDn>                               / stopSendConfig = down,
        confRcv   + event<EvAdminDown>                          / stopSendConfig = down,
        confRcv   + event<EvNewConfErr>                         / sendConfigNack = confRcv,
        confRcv   + event<EvReconfig>                                            = confRcv,
        confRcv   + event<EvNewConfOK>                          / sendConfigAck  = active,
        active    + event<EvCCDn>                               / stopSendHello  = down,
        active    + event<EvAdminDown>                          / setCCDownFlag  = goingDown,
        active    + event<EvNbrGoesDn>                          / stopSendHello  = down,
        active    + event<EvReconfig>                           / sendConfig     = confSnd,
        active    + event<EvHoldTimer> [ activeConfig ]         / sendConfig     = confSnd,
        active    + event<EvHoldTimer> [ passiveConfig ]        / stopSendHello  = confRcv,
        active    + event<EvNewConfErr>                         / sendConfigNack = confRcv,
        active    + event<EvNewConfOK>                                           = active,
        active    + event<EvSeqNumErr>                                           = active,
        active    + event<EvHelloRet>                           / sendHello      = active,
        active    + event<EvHelloRcvd>                                           = up,
        up        + event<EvCCDn>                               / stopSendHello  = down,
        up        + event<EvAdminDown>                          / setCCDownFlag  = goingDown,
        up        + event<EvNbrGoesDn>                          / stopSendHello  = down,
        up        + event<EvReconfig>                           / sendConfig     = confSnd,
        up        + event<EvHoldTimer> [ activeConfig ]         / sendConfig     = confSnd,
        up        + event<EvHoldTimer> [ passiveConfig ]        / stopSendHello  = confRcv,
        up        + event<EvNewConfErr>                         / sendConfigNack = confRcv,
        up        + event<EvNewConfOK>                                           = active,
        up        + event<EvSeqNumErr>                                           = up,
        up        + event<EvHelloRet>                           / sendHello      = up,
        up        + event<EvHelloRcvd>                                           = up,
        goingDown + event<EvNbrGoesDn>                          / stopSendHello  = down,
        goingDown + event<EvDownTimer>                          / stopSendHello  = down
      );
    }
      // clang-format on
    //    Start       Event         Next        Action                           Guard
    //  +-----------+-------------+-----------+--------------------------------+----------------------+
//      Row < Down      , EvBringUp   , ConfSnd   , SendConfig                     , ActiveConfig         >,
//      Row < Down      , EvBringUp   , ConfRcv   , NoAction                       , PassiveConfig        >,
    //  +-----------+-------------+-----------+--------------------------------+----------------------+
//      Row < ConfSnd   , EvCCDn      , Down      , StopSendConfig                 , none                 >,
//      Row < ConfSnd   , EvAdminDown , Down      , StopSendConfig                 , none                 >,
//      Row < ConfSnd   , EvConfErr   , ConfSnd   , SendConfig                     , none                 >,
//      Row < ConfSnd   , EvContenWin , ConfSnd   , NoAction                       , none                 >,
//      Row < ConfSnd   , EvReconfig  , ConfSnd   , SendConfig                     , none                 >,
//      Row < ConfSnd   , EvConfRet   , ConfSnd   , ResendConfig                   , none                 >,
//      Row < ConfSnd   , EvContenLost, ConfRcv   , ActionSequence_
//                                                  <mpl::vector<SendConfigNack,
//                                                               StopSendConfig> > , NotAcceptableConfig  >,
//      Row < ConfSnd   , EvConfDone  , Active    , ActionSequence_
//                                                  <mpl::vector<StopSendConfig,
//                                                               SendHello> >      , none                 >,
//      Row < ConfSnd   , EvContenLost, Active    , ActionSequence_
//                                                  <mpl::vector<StopSendConfig,
//                                                               SendConfigAck,
//                                                               SendHello> >      , AcceptableConfig     >,
    //  +-----------+-------------+-----------+--------------------------------+----------------------+
//      Row < ConfRcv   , EvCCDn      , Down      , NoAction                       , none                 >,
//      Row < ConfRcv   , EvAdminDown , Down      , NoAction                       , none                 >,
//      Row < ConfRcv   , EvNewConfErr, ConfRcv   , SendConfigNack                 , none                 >,
//      Row < ConfRcv   , EvReconfig  , ConfRcv   , NoAction                       , none                 >,
//      Row < ConfRcv   , EvNewConfOK , Active    , ActionSequence_
//                                                  <mpl::vector<SendConfigAck,
//                                                               SendHello> >      , none                 >,
    //  +-----------+-------------+-----------+--------------------------------+----------------------+
//      Row < Active    , EvCCDn      , Down      , StopSendHello                  , none                 >,
//      Row < Active    , EvAdminDown , GoingDown , SetCCDownFlag                  , none                 >,
//      Row < Active    , EvNbrGoesDn , Down      , StopSendHello                  , none                 >,
//      Row < Active    , EvReconfig  , ConfSnd   , ActionSequence_
//                                                  <mpl::vector<SendConfig,
//                                                               StopSendHello> >  , none                 >,
//      Row < Active    , EvHoldTimer , ConfSnd   , ActionSequence_
//                                                  <mpl::vector<SendConfig,
//                                                               StopSendHello> >  , ActiveConfig         >,
//      Row < Active    , EvHoldTimer , ConfRcv   , StopSendHello                  , PassiveConfig        >,
//      Row < Active    , EvNewConfErr, ConfRcv   , ActionSequence_
//                                                  <mpl::vector<SendConfigNack,
//                                                               StopSendHello> >  , none                 >,
//      Row < Active    , EvNewConfOK , Active    , NoAction                       , none                 >,
//      Row < Active    , EvSeqNumErr , Active    , NoAction                       , none                 >,
//      Row < Active    , EvHelloRet  , Active    , SendHello                      , none                 >,
//      Row < Active    , EvHelloRcvd , Up        , NoAction                       , none                 >,
    //  +-----------+-------------+-----------+--------------------------------+----------------------+
//      Row < Up        , EvCCDn      , Down      , StopSendHello                  , none                 >,
//      Row < Up        , EvAdminDown , GoingDown , SetCCDownFlag                  , none                 >,
//      Row < Up        , EvNbrGoesDn , Down      , StopSendHello                  , none                 >,
//      Row < Up        , EvReconfig  , ConfSnd   , ActionSequence_
//                                                  <mpl::vector<SendConfig,
//                                                               StopSendHello> >  , none                 >,
//      Row < Up        , EvHoldTimer , ConfSnd   , ActionSequence_
//                                                  <mpl::vector<SendConfig,
//                                                               StopSendHello> >  , ActiveConfig         >,
//      Row < Up        , EvHoldTimer , ConfRcv   , StopSendHello                  , PassiveConfig        >,
//      Row < Up        , EvNewConfErr, ConfRcv   , ActionSequence_
//                                                  <mpl::vector<SendConfigNack,
//                                                               StopSendHello> >  , none                 >,
//      Row < Up        , EvNewConfOK , Active    , NoAction                       , none                 >,
//      Row < Up        , EvSeqNumErr , Up        , NoAction                       , none                 >,
//      Row < Up        , EvHelloRet  , Up        , SendHello                      , none                 >,
//      Row < Up        , EvHelloRcvd , Up        , NoAction                       , none                 >,
    //  +-----------+-------------+-----------+--------------------------------+----------------------+
//      Row < GoingDown , EvNbrGoesDn , Down      , StopSendHello                  , none                 >,
//      Row < GoingDown , EvDownTimer , Down      , StopSendHello                  , none                 >
    //  +-----------+-------------+-----------+--------------------------------+----------------------+

    inline bool isActiveConfig() const { return m_activeConfig; }

    inline bool isConfigAcceptable(const EvContenLost& eventContenLost) const
    { return eventContenLost.m_configMsg.validConfig; }
    void sendConfigMsg() { std::cout << "sendConfig" << std::endl; }
    void stopSendConfigMsg() { std::cout << "stopSendConfigMsg" << std::endl; }
    void resendConfigMsg() { std::cout << "resendConfigMsg" << std::endl; }
    void sendConfigNackMsg() { std::cout << "sendConfigNackMsg" << std::endl; }
    void sendConfigAckMsg() { std::cout << "sendConfigAckMsg" << std::endl; }
    void sendHelloMsg() { std::cout << "sendHelloMsg" << std::endl; }
    void stopSendHelloMsg() { std::cout << "stopSendHelloMsg" << std::endl; }
    void setCCDownFlagOnMsg() { std::cout << "setCCDownFlagOnMsg" << std::endl; }
    bool  m_activeConfig;
  };

  template <class TEvent> bool ActiveConfig::operator()(ControlChannelFSM& ccFsm, const TEvent&) const
  { return ccFsm.isActiveConfig(); }
  template <class TEvent> bool PassiveConfig::operator()(const ControlChannelFSM& ccFsm, const TEvent&) const
  { return !ccFsm.isActiveConfig(); }

  template <class TEvent> bool AcceptableConfig::operator()(const ControlChannelFSM& ccFsm, const TEvent& event) const
  { return ccFsm.isConfigAcceptable(event); }
  template <class TEvent> bool NotAcceptableConfig::operator()(const ControlChannelFSM& ccFsm, const TEvent& event) const
  { return !ccFsm.isConfigAcceptable(event); }

  template <class TEvent> void SendConfig::operator()(ControlChannelFSM& ccFsm, const TEvent&)
  { ccFsm.sendConfigMsg(); }
  template <class TEvent> void StopSendConfig::operator()(ControlChannelFSM& ccFsm, const TEvent&)
  { ccFsm.stopSendConfigMsg(); }
  template <class TEvent> void ResendConfig::operator()(ControlChannelFSM& ccFsm, const TEvent&)
  { ccFsm.resendConfigMsg(); }
  template <class TEvent> void SendConfigNack::operator()(ControlChannelFSM& ccFsm, const TEvent&)
  { ccFsm.sendConfigNackMsg(); }
  template <class TEvent> void SendConfigAck::operator()(ControlChannelFSM& ccFsm, const TEvent&)
  { ccFsm.sendConfigAckMsg(); }
  template <class TEvent> void SendHello::operator()(ControlChannelFSM& ccFsm, const TEvent&)
  { ccFsm.sendHelloMsg(); }
  template <class TEvent> void StopSendHello::operator()(ControlChannelFSM& ccFsm, const TEvent&)
  { ccFsm.stopSendHelloMsg(); }
  template <class TEvent> void SetCCDownFlag::operator()(ControlChannelFSM& ccFsm, const TEvent&)
  { ccFsm.setCCDownFlagOnMsg(); }

} // namespace cc


int main() {
  using namespace cc;
  ControlChannelFSM controlChannelFsm{true};
  sml::sm<ControlChannelFSM> ccfsm{controlChannelFsm};
  assert(ccfsm.is(down));
  ccfsm.process_event(EvBringUp{});
  assert(ccfsm.is(confSnd));
  ccfsm.process_event(EvConfDone{});
  assert(ccfsm.is(active));
  ccfsm.process_event(EvHelloRcvd{});
  assert(ccfsm.is(up));
}
