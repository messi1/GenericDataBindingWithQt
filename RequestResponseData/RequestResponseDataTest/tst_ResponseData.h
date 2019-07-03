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

#include "TestValues.h"

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

//    fillRequestData(dataToSerialize);

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

//  fillRequestData(dataToSerialize);

  out << dataToSerialize;
  in  >> dataToDeserialize;

  dataToDeserialize.addResponse({RequestCmd::EthState, false, 4});
  dataToDeserialize.setRequestType(RequestType::Command);


  EXPECT_FALSE(dataToSerialize == dataToDeserialize);
}

//-------------------------------------------------------------------------------------------------
TEST(ResponseData, copyRequestData)
{
  RequestData  requestData;
  ResponseData responseData;

  fillRequestData(requestData);

  //responseData = requestData;

//  EXPECT_TRUE(responseData == responseData);

//  RequestList requestKeyList  = responseData.requestMap().keys();
//  RequestList responseKeyList = responseData.requestMap().keys();

//  EXPECT_TRUE(requestKeyList.count() == responseKeyList.count());

//  for(int i = 0; i < requestKeyList.count(); ++i)
//  {
//    EXPECT_TRUE(requestKeyList.at(i) == responseKeyList.at(i));
//  }
}

//-------------------------------------------------------------------------------------------------
//TEST(ResponseData, addRequestPerformance)
//{
//  RequestData responseData;
//  RequestData responseDataSpecialMap;

//  std::clock_t startTime = std::clock();
//  for(unsigned long i = 0; i < 100'000; ++i) {
//    responseData.addRequest( {RequestCmd::Language,  true , 2}, {"11","22","33"}, {"44","55","66"});
//  }
//  std::clock_t endTime = std::clock();
//  std::cout << "Execution time of " << "Without komplex RequestMap object" << " : "
//            << 1000*(endTime-startTime) / CLOCKS_PER_SEC << " ms" << std::endl;


//  startTime = std::clock();
//  for(unsigned long i = 0; i < 100'000; ++i) {
//    responseDataSpecialMap.addRequest( {RequestCmd::Language,  true , 2}, {"11","22","33"}, {"44","55","66"});
//  }
//  endTime = std::clock();
//  std::cout << "Execution time of " << "With komplex RequestMap object" << " : "
//            << 1000*(endTime-startTime) / CLOCKS_PER_SEC << " ms" << std::endl;
//}


//-------------------------------------------------------------------------------------------------
//TEST(ResponseData, checkSetFunction)
//{
//    RequestData responseData;

//    responseData.setRequestType(RequestType::Command);
//    EXPECT_TRUE(responseData.requestType() == RequestType::Command);

//    responseData.setDataClientManager(QSharedPointer<IDataClientManager>(reinterpret_cast<IDataClientManager*>(0x800000)));
//    EXPECT_TRUE(responseData.dataClientManager().data() == reinterpret_cast<IDataClientManager*>(0x800000));
//    responseData.dataClientManager().toStrongRef().reset();
//    EXPECT_FALSE(responseData.dataClientManager().data() == reinterpret_cast<IDataClientManager*>(0x800000));

//    responseData.setDataProxy(reinterpret_cast<IDataProxy*>(0x800001));
//    EXPECT_TRUE(responseData.dataProxy() == reinterpret_cast<IDataProxy*>(0x800001));
//    responseData.setDataProxy(nullptr);
//    EXPECT_FALSE(responseData.dataProxy() == reinterpret_cast<IDataProxy*>(0x800001));

//    responseData.setValueList({RequestCmd::DateTime}, {"11","22","33"});
//    QStringList valueList;
//    responseData.valueList({RequestCmd::DateTime}, valueList);
//    EXPECT_TRUE( (valueList == QStringList{"11","22","33"})  );
//}

//-------------------------------------------------------------------------------------------------
TEST(ResponseData, addResponseWithSameRequest)
{
  Request  request{RequestCmd::WlanList,true, 1};
  TestValues testValues;

  ResponseData responseData;
  QStringList valueList, rangeList, errorList;
  QString accessRights;


  responseData.addResponse(request, testValues.accessRightsList.at(0));

  EXPECT_TRUE(responseData.responseMap().keys().count() == 1 && responseData.responseMap().values().count() == 1 );
  responseData.valueList(request, valueList);
  responseData.rangeList(request, rangeList);
  responseData.errorList(request, errorList);
  accessRights = responseData.accessRights(request);
  EXPECT_TRUE(valueList.isEmpty() &&
              rangeList.isEmpty() &&
              errorList.isEmpty() &&
              accessRights.isEmpty());


  responseData.addResponse(request, testValues.valueList1, testValues.accessRightsList.at(1));

  EXPECT_TRUE(responseData.responseMap().keys().count() == 1 && responseData.responseMap().values().count() == 1 );
  responseData.valueList(request, valueList);
  responseData.rangeList(request, rangeList);
  responseData.errorList(request, errorList);
  accessRights = responseData.accessRights(request);
  EXPECT_TRUE(valueList.count() == testValues.valueList1.count() &&
              rangeList.isEmpty() &&
              errorList.isEmpty() &&
              accessRights == testValues.accessRightsList.at(1));


  responseData.addResponse(request, testValues.valueList2, testValues.rangeList1, testValues.accessRightsList.at(2));

  EXPECT_TRUE(responseData.responseMap().keys().count() == 1 && responseData.responseMap().values().count() == 1 );
  responseData.valueList(request, valueList);
  responseData.rangeList(request, rangeList);
  responseData.errorList(request, errorList);
  accessRights = responseData.accessRights(request);
  EXPECT_TRUE(valueList.count() == testValues.valueList2.count() &&
              rangeList.count() == testValues.rangeList1.count() &&
              errorList.isEmpty() &&
              accessRights == testValues.accessRightsList.at(2));


  responseData.addResponse(request, testValues.valueList1, testValues.rangeList2, testValues.errorList1, testValues.accessRightsList.at(3));

  EXPECT_TRUE(responseData.responseMap().keys().count() == 1 && responseData.responseMap().values().count() == 1 );
  responseData.valueList(request, valueList);
  responseData.rangeList(request, rangeList);
  responseData.errorList(request, errorList);
  accessRights = responseData.accessRights(request);
  EXPECT_TRUE(valueList.count() == testValues.valueList1.count() &&
              rangeList.count() == testValues.rangeList2.count() &&
              errorList.count() == testValues.errorList1.count() &&
              accessRights == testValues.accessRightsList.at(3));

}

//-------------------------------------------------------------------------------------------------
TEST(ResponseData, addMultipleRequests)
{
  TestValues testValues;

  ResponseData responseData;
  QStringList valueList, rangeList, errorList;
  QString accessRights;


  responseData.addResponse(testValues.request1, testValues.accessRightsList.at(0));

  EXPECT_TRUE(responseData.responseMap().keys().count() == 1 && responseData.responseMap().values().count() == 1 );
  responseData.valueList(testValues.request1, valueList);
  responseData.rangeList(testValues.request1, rangeList);
  responseData.errorList(testValues.request1, errorList);
  accessRights = responseData.accessRights(testValues.request1);
  EXPECT_TRUE(valueList.isEmpty() &&
              rangeList.isEmpty() &&
              errorList.isEmpty() &&
              accessRights.isEmpty());


  responseData.addResponse(testValues.request2, testValues.valueList1, testValues.accessRightsList.at(1));

  EXPECT_TRUE(responseData.responseMap().keys().count() == 2 && responseData.responseMap().values().count() == 2 );
  responseData.valueList(testValues.request2, valueList);
  responseData.rangeList(testValues.request2, rangeList);
  responseData.errorList(testValues.request2, errorList);
  accessRights = responseData.accessRights(testValues.request2);
  EXPECT_TRUE(valueList.count() == testValues.valueList1.count() &&
              rangeList.isEmpty() &&
              errorList.isEmpty() &&
              accessRights == testValues.accessRightsList.at(1));


  responseData.addResponse(testValues.request3, testValues.valueList2, testValues.rangeList1, testValues.accessRightsList.at(2));

  EXPECT_TRUE(responseData.responseMap().keys().count() == 3 && responseData.responseMap().values().count() == 3 );
  responseData.valueList(testValues.request3, valueList);
  responseData.rangeList(testValues.request3, rangeList);
  responseData.errorList(testValues.request3, errorList);
  accessRights = responseData.accessRights(testValues.request3);
  EXPECT_TRUE(valueList.count() == testValues.valueList2.count() &&
              rangeList.count() == testValues.rangeList1.count() &&
              errorList.isEmpty() &&
              accessRights == testValues.accessRightsList.at(2));


  responseData.addResponse(testValues.request4, testValues.valueList1, testValues.rangeList2, testValues.errorList1, testValues.accessRightsList.at(3));

  EXPECT_TRUE(responseData.responseMap().keys().count() == 4 && responseData.responseMap().values().count() == 4 );
  responseData.valueList(testValues.request4, valueList);
  responseData.rangeList(testValues.request4, rangeList);
  responseData.errorList(testValues.request4, errorList);
  accessRights = responseData.accessRights(testValues.request4);
  EXPECT_TRUE(valueList.count() == testValues.valueList1.count() &&
              rangeList.count() == testValues.rangeList2.count() &&
              errorList.count() == testValues.errorList1.count() &&
              accessRights == testValues.accessRightsList.at(3));
}
