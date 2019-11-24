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

#include "RequestResponseData/RequestCommand.h"
#include "RequestResponseData/RequestData.h"

#include "TestRequestValues.h"
#include "TestResponseValues.h"

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

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
  RequestData requestData1;
  RequestData requestData2;

  fillRequestData(requestData1);

  EXPECT_FALSE(requestData1 == requestData2);

  requestData2 = requestData1;

  EXPECT_TRUE(requestData1 == requestData2);

  RequestList requestKeyList1  = requestData1.requestMap().keys();
  RequestList requestKeyList2 = requestData2.requestMap().keys();

  EXPECT_TRUE(requestKeyList1.count() == requestKeyList2.count());

  for(int i = 0; i < requestKeyList1.count(); ++i)
  {
    EXPECT_TRUE(requestKeyList1.at(i) == requestKeyList2.at(i));
  }
}

//-------------------------------------------------------------------------------------------------
TEST(RequestData, addRequestPerformance)
{
  RequestData requestData;
  RequestData requestDataSpecialMap;

  std::clock_t startTime = std::clock();
  for(unsigned long i = 0; i < 100'000; ++i) {
    requestData.addRequest( {RequestCmd::Language,  true , 2}, {"11","22","33"});
  }
  std::clock_t endTime = std::clock();
  std::cerr << "Execution time of " << "Without komplex RequestMap object" << " : "
            << 1000*(endTime-startTime) / CLOCKS_PER_SEC << " ms\n";


  startTime = std::clock();
  for(unsigned long i = 0; i < 100'000; ++i) {
    requestDataSpecialMap.addRequest( {RequestCmd::Language,  true , 2}, {"11","22","33"});
  }
  endTime = std::clock();
  std::cerr << "Execution time of " << "With komplex RequestMap object" << " : "
            << 1000*(endTime-startTime) / CLOCKS_PER_SEC << " ms\n";
}


//-------------------------------------------------------------------------------------------------
void myDeleter1(IDataClientManager*){}
void myDeleter2(IDataProxy*){}

TEST(RequestData, checkSetFunction)
{
    RequestData requestData;

    requestData.setRequestType(RequestType::Command);
    EXPECT_TRUE(requestData.requestType() == RequestType::Command);

    QSharedPointer<IDataClientManager> test_DCM_Ptr = QSharedPointer<IDataClientManager>(reinterpret_cast<IDataClientManager*>(0x800000), myDeleter1);
    QSharedPointer<IDataProxy> testDataProxyPtr = QSharedPointer<IDataProxy>(reinterpret_cast<IDataProxy*>(0x800001), myDeleter2);

    requestData.setDataClientManager(test_DCM_Ptr.toWeakRef());
    EXPECT_TRUE(requestData.dataClientManager() == test_DCM_Ptr.toWeakRef());
    requestData.setDataClientManager({});
    EXPECT_FALSE(requestData.dataClientManager() == test_DCM_Ptr.toWeakRef());

    requestData.setDataProxy(testDataProxyPtr.toWeakRef());
    EXPECT_TRUE(requestData.dataProxy() == testDataProxyPtr.toWeakRef());
    requestData.setDataProxy({});
    EXPECT_FALSE(requestData.dataProxy() == testDataProxyPtr.toWeakRef());

    requestData.setValueList({RequestCmd::DateTime}, {"11","22","33"});
    QStringList valueList;
    requestData.valueList({RequestCmd::DateTime}, valueList);
    EXPECT_TRUE( (valueList == QStringList{"11","22","33"})  );
}

//-------------------------------------------------------------------------------------------------
TEST(RequestData, addRequestsWithSameRequest)
{
    Request request{RequestCmd::WlanList, true, 1};
    TestRequestValues testValues;
    RequestData requestData;
    QStringList valueList;

    requestData.addRequest(request);
    EXPECT_TRUE(requestData.requestMap().keys().count() == 1 && requestData.requestMap().values().count() == 1);
    requestData.valueList(request, valueList);
    EXPECT_TRUE(valueList.isEmpty());


    requestData.addRequest(request, testValues.valueList1);
    EXPECT_TRUE(requestData.requestMap().keys().count() == 1 && requestData.requestMap().values().count() == 1 );

    requestData.valueList(request, valueList);
    EXPECT_TRUE(valueList.count() == testValues.valueList1.count());

    requestData.addRequest(request, testValues.valueList2);
    EXPECT_TRUE(requestData.requestMap().keys().count() == 1 && requestData.requestMap().values().count() == 1 );
    requestData.valueList(request, valueList);
    EXPECT_TRUE(valueList.count() == testValues.valueList2.count() );
}

//-------------------------------------------------------------------------------------------------
TEST(RequestData, addMultipleRequests)
{
    TestRequestValues testValues;
    RequestData requestData;
    QStringList valueList;

    requestData.addRequest(testValues.request1);
    EXPECT_TRUE(requestData.requestMap().keys().count() == 1
                && requestData.requestMap().values().count() == 1);
    requestData.valueList(testValues.request1, valueList);
    EXPECT_TRUE(valueList.isEmpty());

    requestData.addRequest(testValues.request1);
    requestData.addRequest(testValues.request2, testValues.valueList1);
    requestData.valueList(testValues.request2, valueList);
    EXPECT_TRUE(requestData.requestMap().keys().count() == 2
                && requestData.requestMap().values().count() == 2);
    EXPECT_TRUE(valueList.count() == testValues.valueList1.count());

    requestData.addRequest(testValues.request3, testValues.valueList2);
    EXPECT_TRUE(requestData.requestMap().keys().count() == 3
                && requestData.requestMap().values().count() == 3);
    requestData.valueList(testValues.request3, valueList);
    EXPECT_TRUE(valueList.count() == testValues.valueList2.count());
}

//-------------------------------------------------------------------------------------------------
TEST(RequestData, addRequestList)
{
    TestRequestValues testValues;
    RequestData requestData;

    requestData.addRequestList(
        {testValues.request1, testValues.request1, testValues.request1, testValues.request1});
    EXPECT_TRUE(requestData.requestMap().keys().count() == 1);

    requestData.addRequestList({testValues.request1,
                                testValues.request2,
                                testValues.request3,
                                testValues.request4,
                                testValues.request5});
    EXPECT_TRUE(requestData.requestMap().keys().count() == 5);

    requestData.clearRequestMap();
    EXPECT_TRUE(requestData.requestMap().keys().isEmpty());
}
