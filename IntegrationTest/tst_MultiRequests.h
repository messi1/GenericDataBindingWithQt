#ifndef TST_MULTIREQUESTS_H
#define TST_MULTIREQUESTS_H

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
#include <QThread>
#include <QTimer>

#include "DataProvider/DataProvider.h"
#include "DataProvider/DataProxy.h"
#include "RequestResponseData/RequestCommand.h"
#include "RequestResponseData/RequestData.h"

#include "MockConnector.h"

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;


TEST(Integration, multiRequests)
{
    QEventLoop waitForLoop;
    QTimer     quitEventLoopTimer;
    RequestData   testRequestData = TestRequestValues().requestData1;
    MockConnector mockConnector;
    DataProvider dataProvider(mockConnector);
    DataProxy dataProxy(dataProvider, nullptr);

    QThread* dataThread = new QThread;
    dataThread->setObjectName("dataThread");
    dataProvider.moveToThread(dataThread);

    QObject::connect(&quitEventLoopTimer, &QTimer::timeout, [&waitForLoop]()
    {
      waitForLoop.quit();
      FAIL();
    });

    QObject::connect(&dataProxy, SIGNAL(sigRequestData(const RequestData &)), dynamic_cast<QObject*>(&dataProvider), SLOT(requestData(const RequestData &)), Qt::QueuedConnection);
    QObject::connect(&dataProxy, &DataProxy::sigResponseData, [testRequestData, &waitForLoop](const ResponseData &responseData)
    {
      //Async code
      EXPECT_GE(responseData.responseMap().count(), testRequestData.requestMap().count());
      ASSERT_GE(responseData.responseMap().count(), testRequestData.requestMap().count());
      EXPECT_TRUE( responseData.requestType() == testRequestData.requestType() );

      QMapIterator requestItr(testRequestData.requestMap());
      QMapIterator responseItr(responseData.responseMap());

      while(requestItr.hasNext() && requestItr.hasNext())
      {
          responseItr.next();

          EXPECT_TRUE( requestItr.key()   == responseItr.key() );
//          EXPECT_TRUE( requestItr.value() == responseItr.value() );
      }

      if(waitForLoop.isRunning())
        waitForLoop.exit();
    });

    dataThread->start();
      waitForLoop.exec(); // Wait until the dataThread sends the data
}
#endif // TST_MULTIREQUESTS_H
