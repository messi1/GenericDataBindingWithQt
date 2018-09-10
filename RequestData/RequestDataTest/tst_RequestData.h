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

  data.addRequest(requestList.at(0), valueList1, rangeList1, errorList1);
  data.addRequest(requestList.at(1), valueList1, rangeList2, errorList2);
  data.addRequest(requestList.at(2), valueList1, rangeList3, errorList3);

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

  dataToDeserialize.addRequest({RequestCmd::EthState, false, 4});
  dataToDeserialize.setRequestType(RequestType::Command);


  EXPECT_FALSE(dataToSerialize == dataToDeserialize);
}

//-------------------------------------------------------------------------------------------------
TEST(RequestData, copyRequestData)
{
  RequestData requestData;
  RequestData responseData;

  fillRequestData(requestData);

  responseData = requestData;

  EXPECT_TRUE(responseData == requestData);

  RequestList requestKeyList  = requestData.requestMap().keys();
  RequestList responseKeyList = responseData.requestMap().keys();

  EXPECT_TRUE(requestKeyList.count() == responseKeyList.count());

  for(int i = 0; i < requestKeyList.count(); ++i)
  {
    EXPECT_TRUE(requestKeyList.at(i) == responseKeyList.at(i));
  }
}

//-------------------------------------------------------------------------------------------------
//TEST(RequestData, addRequestPerformance)
//{
//  RequestData requestData;
//  RequestData requestDataSpecialMap;

//  std::clock_t startTime = std::clock();
//  for(unsigned long i = 0; i < 100'000; ++i) {
//    requestData.addRequest( {RequestCmd::Language,  true , 2}, {"11","22","33"}, {"44","55","66"});
//  }
//  std::clock_t endTime = std::clock();
//  std::cout << "Execution time of " << "Without komplex RequestMap object" << " : "
//            << 1000*(endTime-startTime) / CLOCKS_PER_SEC << " ms" << std::endl;


//  startTime = std::clock();
//  for(unsigned long i = 0; i < 100'000; ++i) {
//    requestDataSpecialMap.addRequest( {RequestCmd::Language,  true , 2}, {"11","22","33"}, {"44","55","66"});
//  }
//  endTime = std::clock();
//  std::cout << "Execution time of " << "With komplex RequestMap object" << " : "
//            << 1000*(endTime-startTime) / CLOCKS_PER_SEC << " ms" << std::endl;
//}


//-------------------------------------------------------------------------------------------------
TEST(RequestData, checkSetFunction)
{
    RequestData requestData;

    requestData.setRequestType(RequestType::Command);
    EXPECT_TRUE(requestData.requestType() == RequestType::Command);

    requestData.setDataManager(reinterpret_cast<IDataClientManager*>(0x800000));
    EXPECT_TRUE(requestData.dataManager() == reinterpret_cast<IDataClientManager*>(0x800000));
    requestData.setDataManager(nullptr);
    EXPECT_FALSE(requestData.dataManager() == reinterpret_cast<IDataClientManager*>(0x800000));

    requestData.setDataProxy(reinterpret_cast<IDataProxy*>(0x800001));
    EXPECT_TRUE(requestData.dataProxy() == reinterpret_cast<IDataProxy*>(0x800001));
    requestData.setDataProxy(nullptr);
    EXPECT_FALSE(requestData.dataProxy() == reinterpret_cast<IDataProxy*>(0x800001));

    requestData.setValueList({RequestCmd::DateTime}, {"11","22","33"});
    QStringList valueList;
    requestData.valueList({RequestCmd::DateTime}, valueList);
    EXPECT_TRUE( (valueList == QStringList{"11","22","33"})  );
}

//-------------------------------------------------------------------------------------------------
TEST(RequestData, addRequestsWithSameRequest)
{
  Request  request{RequestCmd::WlanList,true, 1};
  TestValues testValues;

  RequestData requestData;
  QStringList valueList, rangeList, errorList;
  QString accessRights;


  requestData.addRequest(request, testValues.accessRightsList.at(0));

  EXPECT_TRUE(requestData.requestMap().keys().count() == 1 && requestData.requestMap().values().count() == 1 );
  requestData.valueList(request, valueList);
  requestData.rangeList(request, rangeList);
  requestData.errorList(request, errorList);
  accessRights = requestData.accessRights(request);
  EXPECT_TRUE(valueList.isEmpty() &&
              rangeList.isEmpty() &&
              errorList.isEmpty() &&
              accessRights.isEmpty());


  requestData.addRequest(request, testValues.valueList1, testValues.accessRightsList.at(1));

  EXPECT_TRUE(requestData.requestMap().keys().count() == 1 && requestData.requestMap().values().count() == 1 );
  requestData.valueList(request, valueList);
  requestData.rangeList(request, rangeList);
  requestData.errorList(request, errorList);
  accessRights = requestData.accessRights(request);
  EXPECT_TRUE(valueList.count() == testValues.valueList1.count() &&
              rangeList.isEmpty() &&
              errorList.isEmpty() &&
              accessRights == testValues.accessRightsList.at(1));


  requestData.addRequest(request, testValues.valueList2, testValues.rangeList1, testValues.accessRightsList.at(2));

  EXPECT_TRUE(requestData.requestMap().keys().count() == 1 && requestData.requestMap().values().count() == 1 );
  requestData.valueList(request, valueList);
  requestData.rangeList(request, rangeList);
  requestData.errorList(request, errorList);
  accessRights = requestData.accessRights(request);
  EXPECT_TRUE(valueList.count() == testValues.valueList2.count() &&
              rangeList.count() == testValues.rangeList1.count() &&
              errorList.isEmpty() &&
              accessRights == testValues.accessRightsList.at(2));


  requestData.addRequest(request, testValues.valueList1, testValues.rangeList2, testValues.errorList1, testValues.accessRightsList.at(3));

  EXPECT_TRUE(requestData.requestMap().keys().count() == 1 && requestData.requestMap().values().count() == 1 );
  requestData.valueList(request, valueList);
  requestData.rangeList(request, rangeList);
  requestData.errorList(request, errorList);
  accessRights = requestData.accessRights(request);
  EXPECT_TRUE(valueList.count() == testValues.valueList1.count() &&
              rangeList.count() == testValues.rangeList2.count() &&
              errorList.count() == testValues.errorList1.count() &&
              accessRights == testValues.accessRightsList.at(3));

}
