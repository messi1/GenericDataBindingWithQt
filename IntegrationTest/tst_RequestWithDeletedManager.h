#ifndef TST_REQUESTWITHDELETEDMANAGER_H
#define TST_REQUESTWITHDELETEDMANAGER_H

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

#include <QDebug>
#include <QEventLoop>
#include <QSharedPointer>
#include <QThread>
#include <QTimer>

#include "DataBinding/DataClientManager.h"
#include "DataProvider/DataProvider.h"
#include "DataProvider/DataProxy.h"
#include "RequestData/RequestCommand.h"
#include "RequestData/RequestData.h"
#include "RequestBroker/IConnector.h"


#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

#include "DataProvider/DataProviderTest/TestValues.h"

class MockConnector: public IConnector
{
  public:
    bool requestData(const RequestData& requestData, RequestData& responseData) override
    {
        TestValues testData;
        responseData = requestData;

        if( responseData.requestMap() == responseData.requestMap())
        {
          responseData.clearAllData();

          responseData.addRequest(testData.request1);
          responseData.addRequest(testData.request2, testData.valueList1);
          responseData.addRequest(testData.request3, testData.valueList2, testData.rangeList1);
          responseData.addRequest(testData.request4, testData.valueList3, testData.rangeList2, testData.errorList1);

          return true;
        }

        return false;
    }
};

TEST(Integration, requestWithDeletedManager)
{
    QEventLoop waitForLoop;
    QTimer     quitEventLoopTimer;
    RequestData   testResponseData = TestValues().responseData1;
    MockConnector mockConnector;
    DataProvider dataProvider(mockConnector);
    DataProxy dataProxy(dataProvider, nullptr);
    QSharedPointer<IDataClientManager> dataManagerPtr = QSharedPointer<IDataClientManager>(new DataClientManager(dataProxy));
    DataClientManager* dataClientManager = new DataClientManager(dataProxy);

    QThread* dataThread = new QThread;
    dataThread->setObjectName("dataThread");
    dataProvider.moveToThread(dataThread);

    QObject::connect(&quitEventLoopTimer, &QTimer::timeout, [&waitForLoop]()
    {
      waitForLoop.quit();
      FAIL();
    });

    QObject::connect(&dataProxy, SIGNAL(sigRequestData(const RequestData &)), dynamic_cast<QObject*>(&dataProvider), SLOT(requestData(const RequestData &)), Qt::QueuedConnection);
    QObject::connect(&dataProxy, &DataProxy::sigResponseData, [testResponseData, &waitForLoop](const RequestData &responseData)
    {
      //Async code
      EXPECT_GE(responseData.requestMap().count(), testResponseData.requestMap().count());
      ASSERT_GE(responseData.requestMap().count(), testResponseData.requestMap().count());
      EXPECT_TRUE( responseData.requestType() == testResponseData.requestType() );

      QMapIterator<Request, RequestDataMatrix> responseItr(responseData.requestMap());
      QMapIterator<Request, RequestDataMatrix> testResponseItr(testResponseData.requestMap());

      while(testResponseItr.hasNext() && responseItr.hasNext()) {
          testResponseItr.next();
          responseItr.next();

          EXPECT_TRUE( testResponseItr.key()   == responseItr.key() );
          EXPECT_TRUE( testResponseItr.value() == responseItr.value() );

      }

      if(waitForLoop.isRunning())
        waitForLoop.exit();
    });
    quitEventLoopTimer.start(2000);
    dataThread->start();

    RequestData requestData(dataManagerPtr.toWeakRef(), QSharedPointer<IDataProxy>(&dataProxy).toWeakRef());
    requestData.addRequest({RequestCmd::BatteryState});
    requestData.setRequestType(RequestType::GetValues);
    dataClientManager->requestData(requestData);
    dataManagerPtr.clear();
    waitForLoop.exec(); // Wait until the dataThread sends the data
}

#endif // TST_REQUESTWITHDELETEDMANAGER_H
