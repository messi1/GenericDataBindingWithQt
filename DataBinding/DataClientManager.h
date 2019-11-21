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
#include <QSharedPointer>
#include <QString>
#include <QVector>

#include "IDataClientManager.h"
#include "RequestResponseData/RequestData.h"

class IDataProxy;
class IDataClient;

class DataClientManager : public IDataClientManager, public QEnableSharedFromThis<DataClientManager>
{
public:
    explicit DataClientManager(const QSharedPointer<IDataProxy>& dataProxy);
    ~DataClientManager() override;

    [[nodiscard]] DataProxyWeakPtr dataProxy()const override;
    void setDataProxy(const QSharedPointer<IDataProxy> &dataProxy);

    [[nodiscard]] DataClientManager *clone() const override;
    void clearDataClientList();

    void registerClient(const Request& request, IDataClient* dataClient) final;
    void deregisterClient(const Request& request, IDataClient* dataClient) final;
    void deregisterAllClient(IDataClient* dataClient) final;
    void changeRegisteredRequest(IDataClient* dataClient, const Request& oldRequest, const Request& newRequest) final;

    [[nodiscard]] int numberOfRegisterdRequests() const;
    RequestList allClientRequests(IDataClient *dataClient) const;

    void requestGetClientData(IDataClient* dataClient, const Request& request) final;
    void requestGetAllClientData() final;
    void requestData(const RequestData &requestData) final;
    void requestSaveData(const Request& saveRequest,   const QStringList& valueList) final;
    void requestCommand(const Request& commandRequest, const QStringList& valueList) final;

    void newValueReceived( const ResponseData& responseData) override;

private:
    using ClientVector     = QVector<IDataClient*>;
    using ClientRequestMap = QMap<Request, ClientVector>;

    QSharedPointer<IDataProxy> mDataProxy;
    ClientRequestMap           mClientRequestMap;
};

#endif // DATACLIENTMANAGER_H
