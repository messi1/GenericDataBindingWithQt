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
  RequestCmdVector cmdVector{RequestCmd::BatteryState, RequestCmd::EthState, RequestCmd::WlanState};

  const QStringList valueList1{"AA1","BB1","CC1"};
  const QStringList valueList2{"AA2","BB2","CC2"};
  const QStringList valueList3{"AA3","BB3","CC3"};


  const QStringList rangeList1{"111","222","333"};
  const QStringList rangeList2{"444","555","666"};
  const QStringList rangeList3{"777","888","999"};


  const QStringList errorList1{"E1AA","E2BB","E3CC"};
  const QStringList errorList2{"E4AA","E5BB","E6CC"};
  const QStringList errorList3{"E7AA","E8BB","E9CC"};


  const StringMatrix valueMatrix{valueList1, valueList2, valueList3};
  const StringMatrix rangeMatrix{rangeList1, rangeList2, rangeList3};
  const StringMatrix errorMatrix{errorList1, errorList2, errorList3};

  data.setRequestCmdVector(cmdVector);
  data.setValueMatrix(valueMatrix);
  data.setRangeMatrix(rangeMatrix);
  data.setErrorMatrix(errorMatrix);
  data.setRequestType(requestType);
  data.setCompartmentId(2);
  data.setWithRange(true);
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

  EXPECT_TRUE(dataToSerialize.requestCmdVector() == dataToDeserialize.requestCmdVector());
  EXPECT_TRUE(dataToSerialize.valueMatrix()      == dataToDeserialize.valueMatrix());
  EXPECT_TRUE(dataToSerialize.rangeMatrix()      == dataToDeserialize.rangeMatrix());
  EXPECT_TRUE(dataToSerialize.errorMatrix()      == dataToDeserialize.errorMatrix());
  EXPECT_TRUE(dataToSerialize.requestType()      == dataToDeserialize.requestType());
  EXPECT_TRUE(dataToSerialize.compartmentId()    == dataToDeserialize.compartmentId());
  EXPECT_TRUE(dataToSerialize.withRange()        == dataToDeserialize.withRange());
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

  dataToDeserialize.appendRequestCommand(RequestCmd::EthState);
  dataToDeserialize.appendValueList(QStringList());
  dataToDeserialize.appendRangeList(QStringList());
  dataToDeserialize.appendErrorList(QStringList());

  dataToDeserialize.setCompartmentId(3);
  dataToDeserialize.setWithRange(false);
  dataToDeserialize.setRequestType(RequestType::Command);


  EXPECT_FALSE(dataToSerialize.requestCmdVector() == dataToDeserialize.requestCmdVector());
  EXPECT_FALSE(dataToSerialize.valueMatrix()      == dataToDeserialize.valueMatrix());
  EXPECT_FALSE(dataToSerialize.rangeMatrix()      == dataToDeserialize.rangeMatrix());
  EXPECT_FALSE(dataToSerialize.errorMatrix()      == dataToDeserialize.errorMatrix());
  EXPECT_FALSE(dataToSerialize.requestType()      == dataToDeserialize.requestType());
  EXPECT_FALSE(dataToSerialize.compartmentId()    == dataToDeserialize.compartmentId());
  EXPECT_FALSE(dataToSerialize.withRange()        == dataToDeserialize.withRange());
}
