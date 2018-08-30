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

#ifndef MOCKDATAPROVIDER_H
#define MOCKDATAPROVIDER_H

#include <QDebug>
#include <QObject>

#include "DataProvider/IDataProvider.h"
#include "DataProvider/IDataProxy.h"

#include "RequestData/RequestData.h"

#include "TestValues.h"

class MockDataProvider: public QObject, public IDataProvider
{
  Q_OBJECT
  Q_INTERFACES(IDataProvider)

public:
  explicit MockDataProvider(QObject* parent=nullptr)
      :QObject(parent)
  {
    setObjectName("MockDataProvider");
  }

public slots:
  void requestData(const RequestData& requestData) override
  {
    TestValues testData;

    if(requestData.requestMap().keys() == testData.requestData1.requestMap().keys())
    {
      IDataProxy* tmpProxy       = requestData.dataProxy();
      IDataClientManager* tmpDCM = requestData.dataManager();
      testData.responseData1.setDataManager(tmpDCM);
      testData.responseData1.setDataProxy(tmpProxy);
      const_cast<RequestData&>(requestData) = testData.responseData1;
    }

    if(requestData.dataProxy())
      requestData.dataProxy()->sigResponseData(requestData);
  }
};

#endif // MOCKDATAPROVIDER_H
