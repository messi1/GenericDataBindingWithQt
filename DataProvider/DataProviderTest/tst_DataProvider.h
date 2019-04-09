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

#include "DataProvider/DataProvider.h"
#include "RequestData/RequestCommand.h"
#include "RequestData/RequestData.h"

#include "MockConnector.h"
#include "MockDataProxy.h"
#include "TestValues.h"

#include <assert.h>
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

#ifdef DEBUG_BUILD
TEST(DataProvider, emptyRequestData)
{
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";

  RequestData   requestData1;
  MockConnector mockConnector;
  MockDataProxy mockDataProxy1;
  DataProvider* dataProvider  = new DataProvider(mockConnector);

  ASSERT_DEATH(dataProvider->requestData(requestData1), "");
}
#endif

TEST(DataProvider, moveToThread)
{
    MockConnector mockConnector;
    QThread* dataThread = new QThread;
    dataThread->setObjectName("dataThread");

    DataProvider* dataProvider  = new DataProvider(mockConnector);

    QThread* creationThread = dataProvider->thread();

    dataProvider->moveToThread(dataThread);

    QThread* runningThread = dataProvider->thread();

    EXPECT_FALSE(creationThread == runningThread);

    if(dataProvider)
      delete dataProvider;

    if(dataThread)
      dataThread->deleteLater();
}

//-------------------------------------------------------------------------------------------------
TEST(DataProvider, DataPassing_requestValue)
{
  qRegisterMetaType<RequestData>("RequestData");

  MockConnector mockConnector;
  MockDataProxy mockDataProxy1;
  RequestData   testResponseData = TestValues().responseData1;

  QEventLoop waitForLoop;
  QTimer     quitEventLoopTimer;
  QThread*   dataThread = new QThread;
  QSignalSpy spy(&mockDataProxy1, &MockDataProxy::sigResponseData);

  quitEventLoopTimer.setInterval(1200);
  quitEventLoopTimer.setSingleShot(true);
  dataThread->setObjectName("dataThread");

  DataProvider* dataProvider  = new DataProvider(mockConnector);
  RequestData  requestData = TestValues().requestData1;
  testResponseData.setDataProxy(&mockDataProxy1);
  testResponseData.setRequestType(RequestType::GetValues);

  dataProvider->moveToThread(dataThread);

  QObject::connect(&quitEventLoopTimer, &QTimer::timeout, [&waitForLoop]()
  {
    waitForLoop.exit(0);
    FAIL();
  });

  QObject::connect(&mockDataProxy1, SIGNAL(sigRequestData(const RequestData &)), dynamic_cast<QObject*>(dataProvider), SLOT(requestData(const RequestData &)), Qt::QueuedConnection);
  QObject::connect(&mockDataProxy1, &MockDataProxy::sigResponseData, [testResponseData, &waitForLoop](const RequestData &responseData)
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
      waitForLoop.quit();
  });

  dataThread->start();
  quitEventLoopTimer.start();
  mockDataProxy1.requestData(testResponseData);
  waitForLoop.exec(); // Wait until the dataThread sends the data

  // The signal spy counter should be 1
  EXPECT_EQ(spy.count(), 1);

  mockDataProxy1.disconnect();
  dataProvider->disconnect();
  quitEventLoopTimer.stop();

  if(dataProvider)
    delete dataProvider;
}

//-------------------------------------------------------------------------------------------------
TEST(DataProvider, DataPassing_sendValue)
{
  qRegisterMetaType<RequestData>("RequestData");

  MockConnector mockConnector;
  MockDataProxy mockDataProxy1;
  RequestData   testResponseData = TestValues().responseData1;

  QEventLoop waitForLoop;
  QTimer     quitEventLoopTimer;
  QThread*   dataThread = new QThread;
  QSignalSpy spy(&mockDataProxy1, &MockDataProxy::sigResponseData);

  quitEventLoopTimer.setInterval(2000);
  quitEventLoopTimer.setSingleShot(true);
  dataThread->setObjectName("dataThread");

  DataProvider* dataProvider  = new DataProvider(mockConnector);
  RequestData  requestData = TestValues().requestData1;
  requestData.setDataProxy(&mockDataProxy1);
  requestData.setRequestType(RequestType::SetValues);

  dataProvider->moveToThread(dataThread);

  QObject::connect(&quitEventLoopTimer, &QTimer::timeout, [&waitForLoop]()
  {
    waitForLoop.quit();
    FAIL();
  });

  QObject::connect(&mockDataProxy1, SIGNAL(sigRequestData(const RequestData &)), dynamic_cast<QObject*>(dataProvider), SLOT(requestData(const RequestData &)), Qt::QueuedConnection);
  QObject::connect(&mockDataProxy1, &MockDataProxy::sigResponseData, [testResponseData, &waitForLoop](const RequestData &responseData)
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

  dataThread->start();
  quitEventLoopTimer.start();
  mockDataProxy1.requestData(requestData);
  waitForLoop.exec(); // Wait until the dataThread sends the data

  // The signal spy counter should be 1
  EXPECT_EQ(spy.count(), 1);

  mockDataProxy1.disconnect();
  quitEventLoopTimer.stop();

  if(dataProvider)
    delete dataProvider;
}

//-------------------------------------------------------------------------------------------------
