#ifndef REQUEST_COMMAND_H
#define REQUEST_COMMAND_H

#include <type_traits>
#include <QVector>


/* This enum class represents all commands which can be send from the NewGui to the RequestBroker. */

enum class RequestCmd : unsigned int
{
  Language,                // RW
  DateTime,                // RW
  WlanState,               // RW
  WlanList,                // R
  EthState,                // RW
  BatteryState,            // R
  UnitSettings,            // R
  StartFirmwareUpdate,     // Cmd
};

struct RequestCmdData {
  RequestCmd     requestCmd;
  bool           withRange     = false;
  unsigned short compartmentId = 0;    // Compartment id starting from 1. 0 is for the platform
};

template <typename E>
constexpr typename std::underlying_type<E>::type to_underlying(E e) noexcept
{
  return static_cast<typename std::underlying_type<E>::type>(e);
}
using RequestPair       = QPair<RequestCmd, int>; // A pair of RequestCmd and compartment id
using RequestCmdVector  = QVector<RequestCmd>;

#endif // REQUEST_COMMAND_H
