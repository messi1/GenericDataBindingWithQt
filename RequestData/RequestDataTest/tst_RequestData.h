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

#include <QDataStream>
#include <QDebug>
#include <QEventLoop>
#include <QThread>
#include <QTimer>

#include "RequestData/RequestCommand.h"
#include "RequestData/RequestData.h"

#include "TestValues.h"

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

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

  data.appendRequest(requestList.at(0), valueList1, rangeList1, errorList1);
  data.appendRequest(requestList.at(1), valueList1, rangeList2, errorList2);
  data.appendRequest(requestList.at(2), valueList1, rangeList3, errorList3);

  data.setRequestType(requestType);
}

TEST(RequestData, serialize_deserialize)
{
  QByteArray  byteArray;
  QDataStream out(&byteArray, QIODevice::WriteOnly);
  QDataStream in(&byteArray,  QIODevice::ReadOnly);

  RequestData dataToSerialize;
  RequestData dataToDeserialize;

  fillRequestData(dataToSerialize);

  out << dataToSerialize;
  in  >> dataToDeserialize;

  EXPECT_TRUE(dataToSerialize == dataToDeserialize);
}

//-------------------------------------------------------------------------------------------------
TEST(RequestData, bad_deserialize)
{
  QByteArray  byteArray;
  QDataStream out(&byteArray, QIODevice::WriteOnly);
  QDataStream in(&byteArray,  QIODevice::ReadOnly);

  RequestData dataToSerialize;
  RequestData dataToDeserialize;

  fillRequestData(dataToSerialize);

  out << dataToSerialize;
  in  >> dataToDeserialize;

  dataToDeserialize.appendRequest({RequestCmd::EthState, false, 4});
  dataToDeserialize.setRequestType(RequestType::Command);


  EXPECT_FALSE(dataToSerialize == dataToDeserialize);
}
