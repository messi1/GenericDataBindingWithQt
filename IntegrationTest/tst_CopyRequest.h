#ifndef TST_COPYREQUEST_H
#define TST_COPYREQUEST_H
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
#include "RequestResponseData/RequestCommand.h"
#include "RequestResponseData/RequestData.h"

#include "MockConnector.h"

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

TEST(Integration, requestWithDeletedManager)
{
//    QEventLoop waitForLoop;
//    QTimer     quitEventLoopTimer;
//    RequestData   testResponseData = TestValues().responseData1;
//    MockConnector mockConnector;
//    DataProvider dataProvider(mockConnector);
//    QSharedPointer<DataProxy> dataProxyPtr(new DataProxy(dataProvider, nullptr));
//    QSharedPointer<DataClientManager> dataClientManagerPtr = QSharedPointer<DataClientManager> (/*new DataClientManager(dataProxyPtr)*/);

//    RequestData requestData(dataClientManagerPtr, dataProxyPtr);
//    RequestData responseData;
//    requestData.addRequest({RequestCmd::BatteryState});
//    requestData.setRequestType(RequestType::GetValues);
//    responseData.clearAllData();

//    responseData = requestData;

//    EXPECT_TRUE(requestData == responseData);
}
#endif // TST_COPYREQUEST_H
