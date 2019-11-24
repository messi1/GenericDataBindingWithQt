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
#include "RequestResponseData/ResponseData.h"

#include "TestResponseValues.h"

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

TEST(ResponseData, serialize_deserialize)
{
    QByteArray  byteArray;
    QDataStream out(&byteArray, QIODevice::WriteOnly);
    QDataStream in(&byteArray,  QIODevice::ReadOnly);

    ResponseData dataToSerialize;
    ResponseData dataToDeserialize;

    fillResponseData(dataToSerialize);

    out << dataToSerialize;
    in  >> dataToDeserialize;

    EXPECT_TRUE(dataToSerialize == dataToDeserialize);
}

//-------------------------------------------------------------------------------------------------
TEST(ResponseData, bad_deserialize)
{
    QByteArray  byteArray;
    QDataStream out(&byteArray, QIODevice::WriteOnly);
    QDataStream in(&byteArray,  QIODevice::ReadOnly);

    ResponseData dataToSerialize;
    ResponseData dataToDeserialize;

    fillResponseData(dataToSerialize);

    out << dataToSerialize;
    in  >> dataToDeserialize;

    dataToDeserialize.addResponse({RequestCmd::EthState, false, 4});
    dataToDeserialize.setRequestType(RequestType::Command);

    EXPECT_FALSE(dataToSerialize == dataToDeserialize);
}

//-------------------------------------------------------------------------------------------------
TEST(ResponseData, copyRequestData)
{
    ResponseData responseData1;
    ResponseData responseData2;

    fillResponseData(responseData1);

    responseData2 = responseData1;
    EXPECT_TRUE(responseData1 == responseData2);

    RequestList responseKeyList1  = responseData1.responseMap().keys();
    RequestList responseKeyList2 = responseData2.responseMap().keys();
    EXPECT_TRUE(responseKeyList1.count() == responseKeyList2.count());

    for(int i = 0; i < responseKeyList1.count(); ++i)
    {
        EXPECT_TRUE(responseKeyList1.at(i) == responseKeyList2.at(i));
    }
}

//-------------------------------------------------------------------------------------------------
TEST(ResponseData, addRequestPerformance)
{
  ResponseData responseData;
  ResponseData responseDataSpecialMap;

    std::clock_t startTime = std::clock();
    for(unsigned long i = 0; i < 100'000; ++i)
    {
        responseData.addResponse( {RequestCmd::Language,  true , 2}, {"11","22","33"}, {"44","55","66"});
    }
    std::clock_t endTime = std::clock();
    std::cout << "Execution time of " << "Without komplex RequestMap object" << " : "
              << 1000*(endTime-startTime) / CLOCKS_PER_SEC << " ms" << std::endl;


    startTime = std::clock();
    for(unsigned long i = 0; i < 100'000; ++i)
    {
        responseDataSpecialMap.addResponse( {RequestCmd::Language,  true , 2}, {"11","22","33"}, {"44","55","66"});
    }
    endTime = std::clock();
    std::cout << "Execution time of " << "With komplex RequestMap object" << " : "
              << 1000*(endTime-startTime) / CLOCKS_PER_SEC << " ms" << std::endl;
}


//-------------------------------------------------------------------------------------------------
extern void myDeleter1(IDataClientManager*);
extern void myDeleter2(IDataProxy*);
TEST(ResponseData, checkSetFunction)
{
    ResponseData responseData;

    responseData.setRequestType(RequestType::Command);
    EXPECT_TRUE(responseData.requestType() == RequestType::Command);

    QSharedPointer<IDataClientManager> test_DCM_Ptr = QSharedPointer<IDataClientManager>(reinterpret_cast<IDataClientManager*>(0x800000), myDeleter1);
    QSharedPointer<IDataProxy> testDataProxyPtr = QSharedPointer<IDataProxy>(reinterpret_cast<IDataProxy*>(0x800001), myDeleter2);


    responseData.setDataClientManager(test_DCM_Ptr.toWeakRef());
    EXPECT_TRUE(responseData.dataClientManager() == test_DCM_Ptr.toWeakRef());
    responseData.setDataClientManager({});
    EXPECT_FALSE(responseData.dataClientManager() == test_DCM_Ptr.toWeakRef());

    responseData.setDataProxy(testDataProxyPtr.toWeakRef());
    EXPECT_TRUE(responseData.dataProxy() == testDataProxyPtr.toWeakRef());
    responseData.setDataProxy({});
    EXPECT_FALSE(responseData.dataProxy() == testDataProxyPtr.toWeakRef());

    responseData.setValueList({RequestCmd::DateTime}, {"11","22","33"});
    QStringList valueList;
    responseData.valueList({RequestCmd::DateTime}, valueList);
    EXPECT_TRUE( (valueList == QStringList{"11","22","33"})  );
}

//-------------------------------------------------------------------------------------------------
TEST(ResponseData, addResponseWithSameRequest)
{
    Request  request{RequestCmd::WlanList,true, 1};
    TestResponseValues testValues;

    ResponseData responseData;
    QStringList valueList, rangeList, errorList;
    QString accessRights;


    responseData.addResponse(request, testValues.accessRight1);
    EXPECT_TRUE(responseData.responseMap().keys().count() == 1 && responseData.responseMap().values().count() == 1 );
    responseData.valueList(request, valueList);
    responseData.rangeList(request, rangeList);
    responseData.errorList(request, errorList);
    accessRights = responseData.accessRights(request);
    EXPECT_TRUE(valueList.isEmpty() &&
              rangeList.isEmpty() &&
              errorList.isEmpty() &&
              accessRights == testValues.accessRight1 &&
              responseData.responseMap().size() > 0);


    responseData.addResponse(request, testValues.valueList1, testValues.accessRight2);
    EXPECT_TRUE(responseData.responseMap().keys().count() == 1 && responseData.responseMap().values().count() == 1 );
    responseData.valueList(request, valueList);
    responseData.rangeList(request, rangeList);
    responseData.errorList(request, errorList);
    accessRights = responseData.accessRights(request);
    EXPECT_TRUE(valueList.count() == testValues.valueList1.count() &&
              rangeList.isEmpty() &&
              errorList.isEmpty() &&
              accessRights == testValues.accessRight2);


    responseData.addResponse(request, testValues.valueList2, testValues.rangeList1, testValues.accessRight3);

    EXPECT_TRUE(responseData.responseMap().keys().count() == 1 && responseData.responseMap().values().count() == 1 );
    responseData.valueList(request, valueList);
    responseData.rangeList(request, rangeList);
    responseData.errorList(request, errorList);
    accessRights = responseData.accessRights(request);
    EXPECT_TRUE(valueList.count() == testValues.valueList2.count() &&
              rangeList.count() == testValues.rangeList1.count() &&
              errorList.isEmpty() &&
              accessRights == testValues.accessRight3);


    responseData.addResponse(request, testValues.valueList1, testValues.rangeList2, testValues.errorList1, testValues.accessRight4);

    EXPECT_TRUE(responseData.responseMap().keys().count() == 1 && responseData.responseMap().values().count() == 1 );
    responseData.valueList(request, valueList);
    responseData.rangeList(request, rangeList);
    responseData.errorList(request, errorList);
    accessRights = responseData.accessRights(request);
    EXPECT_TRUE(valueList.count() == testValues.valueList1.count() &&
              rangeList.count() == testValues.rangeList2.count() &&
              errorList.count() == testValues.errorList1.count() &&
              accessRights == testValues.accessRight4);
}

//-------------------------------------------------------------------------------------------------
TEST(ResponseData, addMultipleRequests)
{
    TestResponseValues testValues;

    ResponseData responseData;
    QStringList valueList, rangeList, errorList;
    QString accessRights;


    responseData.addResponse(testValues.request1, testValues.accessRight1);

    EXPECT_TRUE(responseData.responseMap().keys().count() == 1 && responseData.responseMap().values().count() == 1 );
    responseData.valueList(testValues.request1, valueList);
    responseData.rangeList(testValues.request1, rangeList);
    responseData.errorList(testValues.request1, errorList);
    accessRights = responseData.accessRights(testValues.request1);
    EXPECT_TRUE(valueList.isEmpty() &&
              rangeList.isEmpty() &&
              errorList.isEmpty() &&
              accessRights == testValues.accessRight1);


  responseData.addResponse(testValues.request2, testValues.valueList1, testValues.accessRight2);

  EXPECT_TRUE(responseData.responseMap().keys().count() == 2 && responseData.responseMap().values().count() == 2 );
  responseData.valueList(testValues.request2, valueList);
  responseData.rangeList(testValues.request2, rangeList);
  responseData.errorList(testValues.request2, errorList);
  accessRights = responseData.accessRights(testValues.request2);
  EXPECT_TRUE(valueList.count() == testValues.valueList1.count() &&
              rangeList.isEmpty() &&
              errorList.isEmpty() &&
              accessRights == testValues.accessRight2);


    responseData.addResponse(testValues.request3, testValues.valueList2, testValues.rangeList1, testValues.accessRight3);

    EXPECT_TRUE(responseData.responseMap().keys().count() == 3 && responseData.responseMap().values().count() == 3 );
    responseData.valueList(testValues.request3, valueList);
    responseData.rangeList(testValues.request3, rangeList);
    responseData.errorList(testValues.request3, errorList);
    accessRights = responseData.accessRights(testValues.request3);
    EXPECT_TRUE(valueList.count() == testValues.valueList2.count() &&
              rangeList.count() == testValues.rangeList1.count() &&
              errorList.isEmpty() &&
              accessRights == testValues.accessRight3);


    responseData.addResponse(testValues.request4, testValues.valueList1, testValues.rangeList2, testValues.errorList1, testValues.accessRight4);

    EXPECT_TRUE(responseData.responseMap().keys().count() == 4 && responseData.responseMap().values().count() == 4 );
    responseData.valueList(testValues.request4, valueList);
    responseData.rangeList(testValues.request4, rangeList);
    responseData.errorList(testValues.request4, errorList);
    accessRights = responseData.accessRights(testValues.request4);
    EXPECT_TRUE(valueList.count() == testValues.valueList1.count() &&
              rangeList.count() == testValues.rangeList2.count() &&
              errorList.count() == testValues.errorList1.count() &&
              accessRights == testValues.accessRight4);
}
