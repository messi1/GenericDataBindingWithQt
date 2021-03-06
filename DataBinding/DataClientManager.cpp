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
#include <QDateTime>
#include <QDebug>
#include "DataClientManager.h"
#include "DataProvider/IDataProxy.h"
#include "IDataClient.h"
#include "RequestResponseData/RequestCommand.h"

//--------------------------------------------------------------------------------------------------------
DataClientManager::DataClientManager(const QSharedPointer<IDataProxy> &dataProxy)
    : mDataProxy(dataProxy) {}

//--------------------------------------------------------------------------------------------------------
DataClientManager::~DataClientManager() { mClientRequestMap.clear(); }

//--------------------------------------------------------------------------------------------------------
DataProxyWeakPtr DataClientManager::dataProxy() const { return mDataProxy; }

//--------------------------------------------------------------------------------------------------------
void DataClientManager::setDataProxy(const QSharedPointer<IDataProxy> &dataProxy)
{
    mDataProxy = dataProxy;
}

//--------------------------------------------------------------------------------------------------------
void DataClientManager::registerClient(const Request &request, IDataClient *dataClient)
{
    if (dataClient)
    {
        if (mClientRequestMap.contains(request))
        {
            if (not mClientRequestMap[request].contains(dataClient))
                mClientRequestMap[request].append(dataClient);
            else
                qDebug() << "registerValue(): Could register client because it is "
                        "already registered ";
        }
        else
        {
            mClientRequestMap.insert(request, ClientVector{dataClient});
        }
    }
}

//--------------------------------------------------------------------------------------------------------
void DataClientManager::deregisterClient(const Request &request, IDataClient *dataClient)
{
    if (dataClient)
    {
        if (mClientRequestMap.contains(request))
        {
            bool isContaining = mClientRequestMap[request].contains(dataClient);

            if (isContaining)
            {
                mClientRequestMap[request].removeAll(dataClient);

                if (mClientRequestMap[request].count() == 0)
                    mClientRequestMap.remove(request);
            }
        }
    }
}

//--------------------------------------------------------------------------------------------------------
void DataClientManager::deregisterAllClient(IDataClient *dataClient)
{
    if (dataClient)
    {
        foreach (ClientVector value, mClientRequestMap)
        {
            value.removeAll(dataClient);
        }
    }
}

//--------------------------------------------------------------------------------------------------------
void DataClientManager::changeRegisteredRequest(IDataClient *dataClient, const Request &oldRequest, const Request &newRequest)
{
    if (dataClient)
    {
        deregisterClient(oldRequest, dataClient);
        registerClient(newRequest, dataClient);
    }
}

//--------------------------------------------------------------------------------------------------------
RequestList DataClientManager::allClientRequests(IDataClient *dataClient) const
{
    RequestList cmdVector;

    if (dataClient)
    {
        ClientRequestMap::const_iterator const_it = mClientRequestMap.constBegin();

        while (const_it != mClientRequestMap.constEnd())
        {
            if (const_it.value().contains(dataClient))
                cmdVector.append(const_it.key());
            ++const_it;
        }
    }

    return cmdVector;
}

//--------------------------------------------------------------------------------------------------------
int DataClientManager::numberOfRegisterdRequests() const
{
    return mClientRequestMap.count();
}

//--------------------------------------------------------------------------------------------------------
DataClientManager *DataClientManager::clone() const
{
    DataClientManager *dataClientManager = new DataClientManager(mDataProxy);
    return dataClientManager;
}

//--------------------------------------------------------------------------------------------------------
void DataClientManager::clearDataClientList()
{
    mClientRequestMap.clear();
}

//--------------------------------------------------------------------------------------------------------
void DataClientManager::requestGetClientData(IDataClient *dataClient, const Request &request)
{
    if (dataClient)
    {
        RequestData requestData(sharedFromThis().toWeakRef(),
                                mDataProxy.toWeakRef());
        // TODO: Add dataClient to the requestData as return path for special single
        // request, like timer based requests.
        requestData.addRequest(request);
        requestData.setRequestType(RequestType::GetValues);

        mDataProxy->requestData(requestData);
    }
}

//--------------------------------------------------------------------------------------------------------
void DataClientManager::requestGetAllClientData()
{
    if (not mClientRequestMap.empty())
    {
        RequestData requestData(sharedFromThis().toWeakRef(), mDataProxy.toWeakRef());
        requestData.setRequestType(RequestType::GetValues);
        requestData.addRequestList(mClientRequestMap.keys());

        mDataProxy->requestData(requestData);
    }
}

//--------------------------------------------------------------------------------------------------------
void DataClientManager::requestData(const RequestData &requestData)
{
    mDataProxy->requestData(requestData);
}

//--------------------------------------------------------------------------------------------------------
void DataClientManager::requestCommand(const Request &commandRequest, const QStringList &valueList)
{
    RequestData requestData(sharedFromThis().toWeakRef(), mDataProxy.toWeakRef());
    requestData.setRequestType(RequestType::Command);
    requestData.addRequest(commandRequest, valueList);

    mDataProxy->requestData(requestData);
}

//--------------------------------------------------------------------------------------------------------
void DataClientManager::requestSaveData(const Request &saveRequest, const QStringList &valueList)
{
    RequestData requestData(sharedFromThis().toWeakRef(), mDataProxy.toWeakRef());
    requestData.setRequestType(RequestType::SetValues);
    requestData.addRequest(saveRequest, valueList);

    mDataProxy->requestData(requestData);
}

//--------------------------------------------------------------------------------------------------------
// Replies from the DataProxy
//--------------------------------------------------------------------------------------------------------
void DataClientManager::newValueReceived(const ResponseData &responseData)
{
    const ResponseMap &responseMap = responseData.responseMap();

    QMapIterator<Request, ResponseValue> responseItr(responseMap);

    while (responseItr.hasNext())
    {
        responseItr.next();
        const ClientVector *clientVector = &mClientRequestMap[responseItr.key()];

        for (auto &client : *clientVector)
        {
            if (not responseItr.value().errorList.empty())
            {
                client->setErrorList(responseItr.key(), responseItr.value().errorList);
            }
            else
            {
                client->setAccessRights(responseItr.value().accessRights);
                client->setValueList(responseItr.key(), responseItr.value().valueList, responseItr.value().rangeList);
            }
        }
    }
}
