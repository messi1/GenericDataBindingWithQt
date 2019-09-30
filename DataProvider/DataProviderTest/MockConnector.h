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

#ifndef MOCKCONNECTOR_H
#define MOCKCONNECTOR_H

#include <QString>

#include "RequestResponseData/RequestData.h"
#include "RequestResponseData/ResponseData.h"
#include "RequestResponseData/RequestCommand.h"
#include "RequestBroker/IConnector.h"
#include "RequestResponseData/RequestResponseDataTest/TestRequestValues.h"
#include "RequestResponseData/RequestResponseDataTest/TestResponseValues.h"

class MockConnector: public IConnector
{
  public:
    bool requestData(const RequestData& requestData, ResponseData& responseData) override
    {
      responseData.clearAllData();
      responseData = TestResponseValues().responseData1;
      responseData.setDataProxy(requestData.dataProxy());
      responseData.setDataClientManager(requestData.dataClientManager());

      return true;
    }
};

#endif // MOCKCONNECTOR_H
