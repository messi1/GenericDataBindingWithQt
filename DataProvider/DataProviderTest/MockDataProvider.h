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

#include "RequestResponseData/RequestData.h"

#include "RequestResponseData/RequestResponseDataTest/TestRequestValues.h"
#include "RequestResponseData/RequestResponseDataTest/TestResponseValues.h"

class MockDataProvider: public QObject, public IDataProvider
{
  Q_OBJECT
  Q_INTERFACES(IDataProvider)

  public:
  explicit MockDataProvider(QObject *parent = nullptr)
      : QObject(parent)
  {
      setObjectName("MockDataProvider");
  }

  public slots:
  void requestData(const RequestData &requestData) override
  {
      TestResponseValues testData;
      ResponseData responseData;

      if (requestData.requestMap().keys() == testData.responseData1.responseMap().keys())
      {
          responseData.setDataProxy(requestData.dataProxy());
          responseData.setDataClientManager(requestData.dataClientManager());
          responseData.setRequestType(requestData.requestType());
          responseData.setResponseMap(testData.responseData1.responseMap());
      }

      if (requestData.dataProxy())
          requestData.dataProxy().toStrongRef()->sigResponseData(responseData);
  }
};

#endif // MOCKDATAPROVIDER_H
