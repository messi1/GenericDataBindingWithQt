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

#ifndef MOCKDATACLIENTMANAGER_H
#define MOCKDATACLIENTMANAGER_H

#include "DataBinding/IDataClientManager.h"

class MockDataClientManager: public IDataClientManager, QEnableSharedFromThis<MockDataClientManager>
{
public:
  MockDataClientManager() = default;
  ~MockDataClientManager()override = default;
  void registerClient(const Request& /*request*/, IDataClient* /*dataClient*/) final {}
  void deregisterClient(const Request& /*request*/, IDataClient* /*dataClient*/) final {}
  void deregisterAllClient(IDataClient* /*dataClient*/) final {}
  void changeRegisteredRequest(IDataClient* /*dataClient*/, const Request& /*oldRequest*/, const Request& /*newRequest*/) final {}

  [[nodiscard]] DataProxyWeakPtr    dataProxy() const final { return {}; }
  [[nodiscard]] IDataClientManager *clone() const final { return nullptr; }

  void requestData(const RequestData& /*requestData*/) final {}
  void requestSaveData(const Request& /*saveRequest*/, const QStringList& /*valueList*/)  final {}
  void requestCommand(const Request& /*commandRequest*/, const QStringList& /*valueList*/) final {}
  void requestGetClientData(IDataClient* /*dataClient*/, const Request& /*request*/) final {}
  void requestGetAllClientData() final {}

  void newValueReceived( const ResponseData &responseData) final { mResponseData = responseData; }

  [[nodiscard]] const ResponseData& responseData() const {return mResponseData;}

private:
  ResponseData mResponseData;
};

#endif // MOCKDATACLIENTMANAGER_H
