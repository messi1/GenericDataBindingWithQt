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

        responseData.clearAllData();
        responseData = testData.responseData1;
        responseData.setDataProxy(requestData.dataProxy());
        responseData.setDataClientManager(requestData.dataClientManager());

        return true;
    }
};

TEST(Integration, requestWithDeletedManager)
{
    QEventLoop waitForLoop;
    QTimer     quitEventLoopTimer;
    RequestData   testResponseData = TestValues().responseData1;
    MockConnector mockConnector;
    DataProvider dataProvider(mockConnector);
    QSharedPointer<DataProxy> dataProxyPtr(new DataProxy(dataProvider, nullptr));
    QSharedPointer<DataClientManager> dataClientManagerPtr = QSharedPointer<DataClientManager> (new DataClientManager(dataProxyPtr));

    QThread* dataThread = new QThread;
    dataThread->setObjectName("dataThread");
    dataProvider.moveToThread(dataThread);

    QObject::connect(&quitEventLoopTimer, &QTimer::timeout, [&waitForLoop]()
    {
      waitForLoop.quit();
      SUCCEED();
    });

    QObject::connect(dataProxyPtr.data(), SIGNAL(sigRequestData(const RequestData &)), dynamic_cast<QObject*>(&dataProvider), SLOT(requestData(const RequestData &)), Qt::QueuedConnection);
    QObject::connect(dataProxyPtr.data(), &DataProxy::sigResponseData, [testResponseData, &waitForLoop](const RequestData &responseData)
    {
      //Async code
      EXPECT_TRUE(responseData.dataClientManager());
      EXPECT_TRUE(responseData.dataClientManager().toStrongRef());

      if(waitForLoop.isRunning())
        waitForLoop.exit();
    });
    quitEventLoopTimer.start(2000);
    dataThread->start();

    RequestData requestData(dataClientManagerPtr, dataProxyPtr);
    requestData.addRequest({RequestCmd::BatteryState});
    requestData.setRequestType(RequestType::GetValues);
    //dataProxyPtr->requestData(requestData);
    dataClientManagerPtr->requestData(requestData);
    dataClientManagerPtr.clear();
    waitForLoop.exec(); // Wait until the dataThread sends the data
}

#endif // TST_REQUESTWITHDELETEDMANAGER_H
