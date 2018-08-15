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

class MockDataClientManager: public IDataClientManager
{

public:

  MockDataClientManager() = default;
  virtual ~MockDataClientManager() = default;
  void registerClient(const RequestCmd /*requestId*/, IDataClient* /*dataClient*/) final {}
  void deregisterClient(const RequestCmd /*requestId*/, IDataClient* /*dataClient*/) final {}
  void deregisterAllClient(IDataClient* /*dataClient*/) final {}
  void changeRegisteredRequestCmd(IDataClient* /*dataClient*/, const RequestCmd /*oldRequestId*/, const RequestCmd /*newRequestId*/) final {}

  virtual IDataProxy* getDataProxy()  const final {return nullptr;}
  virtual IDataClientManager* clone() const final {return nullptr;}

  void requestSaveData(const RequestCmd /*requestCmd*/, const QString& /*requestValue*/)  final {}
  void requestCommand(const RequestCmd /*commandName*/, const QString& /*inRequesteter*/) final {}
  void requestGetClientData(IDataClient* /*dataClient*/, const RequestCmd /*requestCmd*/, bool /*withRange*/ = true) final {}
  void requestGetAllClientData(bool /*withRange*/ = true) final {}

  virtual void newValueReceived( const RequestData &requestData) final { mRequestData = requestData; }
  virtual void newStatusReceived(const RequestData &RequestData) final { mRequestData = RequestData; }

  const RequestData& requestData() const {return mRequestData;}

private:
  RequestData mRequestData;
};

#endif // MOCKDATACLIENTMANAGER_H
