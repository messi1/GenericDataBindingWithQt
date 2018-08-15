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

#ifndef DATACLIENTMANAGER_H
#define DATACLIENTMANAGER_H

#include <QMap>
#include <QString>
#include <QVector>

#include "IDataClientManager.h"
#include "RequestData/RequestData.h"

class IDataProxy;
class IDataClient;

class DataClientManager : public IDataClientManager
{
public:
    DataClientManager() = delete;
    explicit DataClientManager(IDataProxy& dataProxy);
    virtual ~DataClientManager() override;

    virtual IDataProxy* getDataProxy()const override;
    void setDataProxy(IDataProxy &dataProxy);

    virtual DataClientManager *clone() const override;
    void clearDataClientList();

    void registerClient(  const RequestCmd requestCmd, IDataClient* dataClient) final;
    void deregisterClient(const RequestCmd requestCmd, IDataClient* dataClient) final;
    void deregisterAllClient(IDataClient* dataClient) final;
    void changeRegisteredRequestCmd(IDataClient* dataClient, const RequestCmd oldRequestId, const RequestCmd newRequestId) final;

    int numberOfRegisterdRequests() const;
    const RequestCmdVector allRequestCmdOfAClient(IDataClient* dataClient) const;

    void requestGetClientData(IDataClient* dataClient, const RequestCmd requestCmd, bool withRange = true) final;
    void requestGetAllClientData(bool withRange = true) final;
    void requestSaveData(const RequestCmd requestCmd,   const QString& requestValue) final;
    void requestCommand(const RequestCmd commandName, const QString& inRequest)  final;

    void newValueReceived( const RequestData& requestData) final;
    void newStatusReceived(const RequestData& requestData) final;

private:
    using ClientVector     = QVector<IDataClient*>;
    using ClientRequestMap = QMap<RequestCmd, ClientVector>;

    IDataProxy&           mDataProxy;
    ClientRequestMap      mClientRequestMap;
};

#endif // DATACLIENTMANAGER_H
