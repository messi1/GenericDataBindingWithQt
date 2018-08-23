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
  MockDataClientManager mockDataClientManager;
  DataProxy             dataProxy(mockDataProvider);
  TestValues            testData;

  QEventLoop* waitForLoop = new QEventLoop;
  QTimer      quitEventLoopTimer;
  QThread*    dataThread = new QThread;
  QSignalSpy  spy(&dataProxy, &DataProxy::sigResponseData);

  quitEventLoopTimer.setInterval(2000);
  quitEventLoopTimer.setSingleShot(true);
  dataThread->setObjectName("dataThread");

  RequestData  requestData1;
  requestData1.setDataProxy(&dataProxy);
  requestData1.setDataManager(&mockDataClientManager);
  requestData1.setRequestVector(testData.requestVector);

  mockDataProvider.moveToThread(dataThread);

  QObject::connect(&quitEventLoopTimer, &QTimer::timeout, [&waitForLoop]()
  {
    waitForLoop->exit(1);
    FAIL();
  });

  QObject::connect(&dataProxy, &DataProxy::sigResponseData, [testData, &waitForLoop](const RequestData &data)
  {
    //Async code
    EXPECT_EQ(data.valueMatrix().at(0).size(), testData.values1.size());
    ASSERT_EQ(data.valueMatrix().at(0).size(), testData.values1.size());

    for(int i = 0; i < testData.values1.size(); ++i)
    {
      EXPECT_EQ(data.valueMatrix().at(0).at(i), testData.values1.at(i));
    }

    MockDataClientManager* dataClientManager = dynamic_cast<MockDataClientManager*>(data.dataManager());

    if(dataClientManager)
    {
      usleep(1000); // Strange things happen. It seems that the data are not ready yet.
      QStringList valueList = dataClientManager->requestData().valueMatrix().at(0);

      if(valueList.size() > 0)
      {
        for(int i = 0; i < testData.values1.size(); ++i)
        {
          EXPECT_EQ(valueList.at(i), testData.values1.at(i));
        }
      }
    }

    if(waitForLoop->isRunning())
      waitForLoop->quit();
  });

  dataThread->start();
  quitEventLoopTimer.start();
  dataProxy.requestData(requestData1);
  if(waitForLoop->isRunning() == false)
    waitForLoop->exec(); // Wait until the dataThread sends the data

  quitEventLoopTimer.stop();
  dataProxy.disconnect();

  EXPECT_EQ(spy.count(), 1);
}
