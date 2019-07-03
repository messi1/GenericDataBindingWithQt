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
//TEST(RequestData, checkSetFunction)
//{
//    RequestData requestData;

//    requestData.setRequestType(RequestType::Command);
//    EXPECT_TRUE(requestData.requestType() == RequestType::Command);

//    requestData.setDataClientManager(QSharedPointer<IDataClientManager>(reinterpret_cast<IDataClientManager*>(0x800000)));
//    EXPECT_TRUE(requestData.dataClientManager().data() == reinterpret_cast<IDataClientManager*>(0x800000));
//    requestData.dataClientManager().toStrongRef().reset();
//    EXPECT_FALSE(requestData.dataClientManager().data() == reinterpret_cast<IDataClientManager*>(0x800000));

//    requestData.setDataProxy(reinterpret_cast<IDataProxy*>(0x800001));
//    EXPECT_TRUE(requestData.dataProxy() == reinterpret_cast<IDataProxy*>(0x800001));
//    requestData.setDataProxy(nullptr);
//    EXPECT_FALSE(requestData.dataProxy() == reinterpret_cast<IDataProxy*>(0x800001));

//    requestData.setValueList({RequestCmd::DateTime}, {"11","22","33"});
//    QStringList valueList;
//    requestData.valueList({RequestCmd::DateTime}, valueList);
//    EXPECT_TRUE( (valueList == QStringList{"11","22","33"})  );
//}

//-------------------------------------------------------------------------------------------------
//TEST(RequestData, addRequestsWithSameRequest)
//{
//  Request  request{RequestCmd::WlanList,true, 1};
//  TestValues testValues;

//  RequestData requestData;
//  QStringList valueList, rangeList, errorList;
//  QString accessRights;


//  requestData.addRequest(request, testValues.accessRightsList.at(0));

//  EXPECT_TRUE(requestData.requestMap().keys().count() == 1 && requestData.requestMap().values().count() == 1 );
//  requestData.valueList(request, valueList);
//  requestData.rangeList(request, rangeList);
//  requestData.errorList(request, errorList);
//  accessRights = requestData.accessRights(request);
//  EXPECT_TRUE(valueList.isEmpty() &&
//              rangeList.isEmpty() &&
//              errorList.isEmpty() &&
//              accessRights.isEmpty());


//  requestData.addRequest(request, testValues.valueList1, testValues.accessRightsList.at(1));

//  EXPECT_TRUE(requestData.requestMap().keys().count() == 1 && requestData.requestMap().values().count() == 1 );
//  requestData.valueList(request, valueList);
//  requestData.rangeList(request, rangeList);
//  requestData.errorList(request, errorList);
//  accessRights = requestData.accessRights(request);
//  EXPECT_TRUE(valueList.count() == testValues.valueList1.count() &&
//              rangeList.isEmpty() &&
//              errorList.isEmpty() &&
//              accessRights == testValues.accessRightsList.at(1));


//  requestData.addRequest(request, testValues.valueList2, testValues.rangeList1, testValues.accessRightsList.at(2));

//  EXPECT_TRUE(requestData.requestMap().keys().count() == 1 && requestData.requestMap().values().count() == 1 );
//  requestData.valueList(request, valueList);
//  requestData.rangeList(request, rangeList);
//  requestData.errorList(request, errorList);
//  accessRights = requestData.accessRights(request);
//  EXPECT_TRUE(valueList.count() == testValues.valueList2.count() &&
//              rangeList.count() == testValues.rangeList1.count() &&
//              errorList.isEmpty() &&
//              accessRights == testValues.accessRightsList.at(2));


//  requestData.addRequest(request, testValues.valueList1, testValues.rangeList2, testValues.errorList1, testValues.accessRightsList.at(3));

//  EXPECT_TRUE(requestData.requestMap().keys().count() == 1 && requestData.requestMap().values().count() == 1 );
//  requestData.valueList(request, valueList);
//  requestData.rangeList(request, rangeList);
//  requestData.errorList(request, errorList);
//  accessRights = requestData.accessRights(request);
//  EXPECT_TRUE(valueList.count() == testValues.valueList1.count() &&
//              rangeList.count() == testValues.rangeList2.count() &&
//              errorList.count() == testValues.errorList1.count() &&
//              accessRights == testValues.accessRightsList.at(3));

//}

////-------------------------------------------------------------------------------------------------
//TEST(RequestData, addMultipleRequests)
//{
//  TestValues testValues;

//  RequestData requestData;
//  QStringList valueList, rangeList, errorList;
//  QString accessRights;


//  requestData.addRequest(testValues.request1, testValues.accessRightsList.at(0));

//  EXPECT_TRUE(requestData.requestMap().keys().count() == 1 && requestData.requestMap().values().count() == 1 );
//  requestData.valueList(testValues.request1, valueList);
//  requestData.rangeList(testValues.request1, rangeList);
//  requestData.errorList(testValues.request1, errorList);
//  accessRights = requestData.accessRights(testValues.request1);
//  EXPECT_TRUE(valueList.isEmpty() &&
//              rangeList.isEmpty() &&
//              errorList.isEmpty() &&
//              accessRights.isEmpty());


//  requestData.addRequest(testValues.request2, testValues.valueList1, testValues.accessRightsList.at(1));

//  EXPECT_TRUE(requestData.requestMap().keys().count() == 2 && requestData.requestMap().values().count() == 2 );
//  requestData.valueList(testValues.request2, valueList);
//  requestData.rangeList(testValues.request2, rangeList);
//  requestData.errorList(testValues.request2, errorList);
//  accessRights = requestData.accessRights(testValues.request2);
//  EXPECT_TRUE(valueList.count() == testValues.valueList1.count() &&
//              rangeList.isEmpty() &&
//              errorList.isEmpty() &&
//              accessRights == testValues.accessRightsList.at(1));


//  requestData.addRequest(testValues.request3, testValues.valueList2, testValues.rangeList1, testValues.accessRightsList.at(2));

//  EXPECT_TRUE(requestData.requestMap().keys().count() == 3 && requestData.requestMap().values().count() == 3 );
//  requestData.valueList(testValues.request3, valueList);
//  requestData.rangeList(testValues.request3, rangeList);
//  requestData.errorList(testValues.request3, errorList);
//  accessRights = requestData.accessRights(testValues.request3);
//  EXPECT_TRUE(valueList.count() == testValues.valueList2.count() &&
//              rangeList.count() == testValues.rangeList1.count() &&
//              errorList.isEmpty() &&
//              accessRights == testValues.accessRightsList.at(2));


//  requestData.addRequest(testValues.request4, testValues.valueList1, testValues.rangeList2, testValues.errorList1, testValues.accessRightsList.at(3));

//  EXPECT_TRUE(requestData.requestMap().keys().count() == 4 && requestData.requestMap().values().count() == 4 );
//  requestData.valueList(testValues.request4, valueList);
//  requestData.rangeList(testValues.request4, rangeList);
//  requestData.errorList(testValues.request4, errorList);
//  accessRights = requestData.accessRights(testValues.request4);
//  EXPECT_TRUE(valueList.count() == testValues.valueList1.count() &&
//              rangeList.count() == testValues.rangeList2.count() &&
//              errorList.count() == testValues.errorList1.count() &&
//              accessRights == testValues.accessRightsList.at(3));
//}
