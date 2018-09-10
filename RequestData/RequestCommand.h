#ifndef REQUEST_COMMAND_H
#define REQUEST_COMMAND_H

#include <type_traits>
#include <QVector>


/* This enum class represents all commands which can be send from the NewGui to the RequestBroker. */

enum class RequestType
{
  GetValues,
  SetValues,
  Command,
  Status,
  _MaxCount
};

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
  _MaxCount
};

struct Request {
  RequestCmd     requestCmd;
  bool           withRange  = false; // Ask specific for the value range (Min/Max)
  unsigned short contextId   = 0;     // Context id starting from "1". A "0" is for the general
};

template <typename E>
constexpr typename std::underlying_type<E>::type to_underlying(E e) noexcept
{
  return static_cast<typename std::underlying_type<E>::type>(e);
}

bool operator==(const Request& request1, const Request& request2);
bool operator<(const Request& request1, const Request& request2);

#endif // REQUEST_COMMAND_H
