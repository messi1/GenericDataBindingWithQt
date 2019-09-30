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
//#include "RequestResponseData/RequestResponseDataTest/TestRequestValues.h"
//#include "RequestResponseData/RequestResponseDataTest/TestResponseValues.h"

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

TEST(DataProxy, requestData)
{
  qRegisterMetaType<RequestData>("RequestData");
  qRegisterMetaType<ResponseData>("ResponseData");

  MockDataProvider      mockDataProvider;
  MockDataClientManager mockDataClientManager;
  DataProxy             dataProxy(mockDataProvider);

  QEventLoop* waitForLoop = new QEventLoop;
  QTimer      quitEventLoopTimer;
  QThread*    dataThread = new QThread;
  QSignalSpy  spy(&dataProxy, &DataProxy::sigResponseData);

  quitEventLoopTimer.setInterval(200000);
  quitEventLoopTimer.setSingleShot(true);
  dataThread->setObjectName("dataThread");

  ResponseData  testResponseData = TestResponseValues().responseData1;
  RequestData   requestData      = TestRequestValues().requestData1;
  requestData.setDataProxy(&dataProxy);
  requestData.setDataClientManager(&mockDataClientManager);

  mockDataProvider.moveToThread(dataThread);

  QObject::connect(&quitEventLoopTimer, &QTimer::timeout, [&waitForLoop]()
  {
    waitForLoop->exit(1);
    FAIL();
  });

  QObject::connect(&dataProxy, &DataProxy::sigResponseData, [testResponseData, &waitForLoop](const ResponseData &responseData)
  {
    //Async code
    EXPECT_EQ(responseData.responseMap().count(), testResponseData.responseMap().count());
    ASSERT_EQ(responseData.responseMap().count(), testResponseData.responseMap().count());
    EXPECT_TRUE( responseData.requestType() == testResponseData.requestType() );

    QMapIterator<Request, ResponseValue> responseItr(responseData.responseMap());
    QMapIterator<Request, ResponseValue> testResponseItr(testResponseData.responseMap());

    while(testResponseItr.hasNext() && responseItr.hasNext())
    {
        testResponseItr.next();
        responseItr.next();

        EXPECT_TRUE( testResponseItr.key()   == responseItr.key() );
        EXPECT_TRUE( testResponseItr.value() == responseItr.value() );
    }

    MockDataClientManager* dataClientManager = dynamic_cast<MockDataClientManager*>(responseData.dataClientManager());

    if(dataClientManager)
    {
      QMapIterator<Request, ResponseValue> responseItr(dataClientManager->responseData().responseMap());
      QMapIterator<Request, ResponseValue> testResponseItr(testResponseData.responseMap());

      usleep(1000); // Strange things happen. It seems that the data are not ready yet.

      while(testResponseItr.hasNext() && responseItr.hasNext())
      {
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
  dataProxy.requestData(requestData);


  if(waitForLoop->isRunning() == false)
    waitForLoop->exec(); // Wait until the dataThread sends the data

  quitEventLoopTimer.stop();
  dataProxy.disconnect();

  EXPECT_EQ(spy.count(), 1);
}
