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
#include <QSignalSpy>
#include <QThread>
#include <QTimer>

#include "DataProvider/DataProxy.h"
#include "MockDataClientManager.h"
#include "MockDataProvider.h"
#include "TestValues.h"

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

TEST(DataProxy, requestData)
{
  qRegisterMetaType<RequestData>("RequestData");

  MockDataProvider      mockDataProvider;
  QSharedPointer<MockDataClientManager> mockDataClientManager;
  QSharedPointer<DataProxy>             dataProxy(new DataProxy(mockDataProvider));
  TestValues            testData;

  QEventLoop* waitForLoop = new QEventLoop;
  QTimer      quitEventLoopTimer;
  QThread*    dataThread = new QThread;
  QSignalSpy  spy(dataProxy.data(), &DataProxy::sigResponseData);

  quitEventLoopTimer.setInterval(200000);
  quitEventLoopTimer.setSingleShot(true);
  dataThread->setObjectName("dataThread");

  RequestData  testResponseData = TestValues().responseData1;
  RequestData  requestData1 = TestValues().requestData1;
  requestData1.setDataProxy(dataProxy);
  requestData1.setDataClientManager(mockDataClientManager);

  mockDataProvider.moveToThread(dataThread);

  QObject::connect(&quitEventLoopTimer, &QTimer::timeout, [&waitForLoop]()
  {
    waitForLoop->exit(1);
    FAIL();
  });

  QObject::connect(dataProxy.data(), &DataProxy::sigResponseData, [testResponseData, &waitForLoop](const RequestData &responseData)
  {
    //Async code
    EXPECT_EQ(responseData.requestMap().count(), testResponseData.requestMap().count());
    ASSERT_EQ(responseData.requestMap().count(), testResponseData.requestMap().count());
    EXPECT_TRUE( responseData.requestType() == testResponseData.requestType() );

    QMapIterator<Request, RequestDataMatrix> responseItr(responseData.requestMap());
    QMapIterator<Request, RequestDataMatrix> testResponseItr(testResponseData.requestMap());

    while(testResponseItr.hasNext() && responseItr.hasNext()) {
        testResponseItr.next();
        responseItr.next();

        EXPECT_TRUE( testResponseItr.key()   == responseItr.key() );
        EXPECT_TRUE( testResponseItr.value() == responseItr.value() );
    }

    MockDataClientManager* dataClientManager = dynamic_cast<MockDataClientManager*>(responseData.dataClientManager().toStrongRef().data());

    if(dataClientManager)
    {
      QMapIterator<Request, RequestDataMatrix> responseItr(dataClientManager->requestData().requestMap());
      QMapIterator<Request, RequestDataMatrix> testResponseItr(testResponseData.requestMap());

      usleep(1000); // Strange things happen. It seems that the data are not ready yet.

      while(testResponseItr.hasNext() && responseItr.hasNext()) {
          testResponseItr.next();
          responseItr.next();

          EXPECT_TRUE( testResponseItr.key()   == responseItr.key() );
          EXPECT_TRUE( testResponseItr.value() == responseItr.value() );
      }
    }

    if(waitForLoop->isRunning())
      waitForLoop->quit();
  });

  dataThread->start();
  quitEventLoopTimer.start();
  dataProxy->requestData(requestData1);
  if(waitForLoop->isRunning() == false)
    waitForLoop->exec(); // Wait until the dataThread sends the data

  quitEventLoopTimer.stop();
  dataProxy->disconnect();

  EXPECT_EQ(spy.count(), 1);
}
