/* Copyright 2018 Juergen Messerer
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef TESTVALUES_H
#define TESTVALUES_H

#include <QStringList>
#include "RequestData/RequestCommand.h"
#include "RequestData/RequestData.h"


struct TestValues
{
  const Request request1{RequestCmd::WlanList,  true};
  const Request request2{RequestCmd::WlanState, false, 1};
  const Request request3{RequestCmd::EthState,  true , 2};

  const Request request4{RequestCmd::BatteryState, false, 3};
  const Request request5{RequestCmd::UnitSettings, true,  4};
  const Request request6{RequestCmd::Language,     false, 5};

  QStringList valueList1 = {"5","10","20",""};
  QStringList valueList2 = {"7","44","33"};
  QStringList rangeList1 = {"true", "false", "true"};
  QStringList rangeList2 = {"false", "true"};
  QStringList errorList1 = {"Error11", "Error14", "Error16"};
  QStringList errorList2 = {"Error13", "Error15"};

  QStringList accessRightsList   = {"", "r", "rw", "rwx"};

  QList<RequestCmd> commandVector{ RequestCmd::WlanList,
                                   RequestCmd::WlanState,
                                   RequestCmd::EthState };
};

void fillRequestData(RequestData& data)
{
  const RequestType requestType = RequestType::GetValues;
  QList<Request> requestList{{RequestCmd::BatteryState, true, 3}, {RequestCmd::EthState, false, 1}, {RequestCmd::WlanState, true, 2}};

  const QStringList valueList1{"AA1","BB1","CC1"};
  const QStringList valueList2{"AA2","BB2","CC2"};
  const QStringList valueList3{"AA3","BB3","CC3"};


  const QStringList rangeList1{"111","222","333"};
  const QStringList rangeList2{"444","555","666"};
  const QStringList rangeList3{"777","888","999"};


  const QStringList errorList1{"E1AA","E2BB","E3CC"};
  const QStringList errorList2{"E4AA","E5BB","E6CC"};
  const QStringList errorList3{"E7AA","E8BB","E9CC"};

  data.addRequest(requestList.at(0), valueList1, rangeList1, errorList1);
  data.addRequest(requestList.at(1), valueList1, rangeList2, errorList2);
  data.addRequest(requestList.at(2), valueList1, rangeList3, errorList3);

  data.setRequestType(requestType);
}

#endif // TESTVALUES_H
