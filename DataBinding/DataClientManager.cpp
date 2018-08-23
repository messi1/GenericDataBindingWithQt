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
#include <QDateTime>


#include "DataClientManager.h"
#include "DataProvider/IDataProxy.h"
#include "IDataClient.h"
#include "RequestData/RequestCommand.h"


//--------------------------------------------------------------------------------------------------------
DataClientManager::DataClientManager(IDataProxy &dataProxy)
  : mDataProxy(dataProxy)
{}

//--------------------------------------------------------------------------------------------------------
DataClientManager::~DataClientManager()
{
    mClientRequestMap.clear();
}

//--------------------------------------------------------------------------------------------------------
IDataProxy *DataClientManager::getDataProxy()const
{
    return &mDataProxy;
}

//--------------------------------------------------------------------------------------------------------
void DataClientManager::setDataProxy(IDataProxy& dataProxy)
{
  mDataProxy = dataProxy;
}

//--------------------------------------------------------------------------------------------------------
void DataClientManager::registerClient(const Request request, IDataClient* dataClient)
{
  if(dataClient)
  {
    if(mClientRequestMap.contains(request))
    {
      if(mClientRequestMap[request].contains(dataClient) == false )
        mClientRequestMap[request].append(dataClient);
      else
        qDebug() << "registerValue(): Could register client because it is already registered ";
    }
    else
    {
      mClientRequestMap.insert(request, ClientVector{dataClient});
    }
  }
}

//--------------------------------------------------------------------------------------------------------
void DataClientManager::deregisterClient(const Request request, IDataClient* dataClient)
{
  if(dataClient)
  {
    if(mClientRequestMap.contains(request))
    {
        bool isContaining = mClientRequestMap[request].contains(dataClient) ;


      if(isContaining)
      {
        mClientRequestMap[request].removeAll(dataClient);

        if(mClientRequestMap[request].count() == 0)
            mClientRequestMap.remove(request);
      }
    }
  }
}

//--------------------------------------------------------------------------------------------------------
void DataClientManager::deregisterAllClient(IDataClient* dataClient)
{
  if(dataClient)
  {
    foreach (ClientVector value, mClientRequestMap)
    {
      value.removeAll(dataClient);
    }
  }
}

//--------------------------------------------------------------------------------------------------------
void DataClientManager::changeRegisteredRequest(IDataClient* dataClient, const Request oldRequest, const Request newRequest)
{
  if(dataClient)
  {
    deregisterClient(oldRequest, dataClient);
    registerClient(newRequest, dataClient);
  }
}

//--------------------------------------------------------------------------------------------------------
const RequestVector DataClientManager::allRequestsOfAClient(IDataClient* dataClient) const
{
    RequestVector cmdVector;

    if(dataClient)
    {
       ClientRequestMap::const_iterator const_it = mClientRequestMap.constBegin();

       while (const_it != mClientRequestMap.constEnd())
       {
           if(const_it.value().contains(dataClient))
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
    DataClientManager* dataClientManager = new DataClientManager( mDataProxy);
    return dataClientManager;
}

//--------------------------------------------------------------------------------------------------------
void DataClientManager::clearDataClientList()
{
  mClientRequestMap.clear();
}

//--------------------------------------------------------------------------------------------------------
void DataClientManager::requestGetClientData(IDataClient* dataClient, const Request &request)
{
  if( dataClient)
  {
    RequestData requestData(this, &mDataProxy);
    // TODO: Add dataClient to the requestData as return path for special single request, like timer based requests.
    requestData.appendRequest(request);
    requestData.setRequestType(RequestType::GetValues);

    mDataProxy.requestData(requestData);
  }
}

//--------------------------------------------------------------------------------------------------------
void DataClientManager::requestGetAllClientData()
{
  if(mClientRequestMap.size() > 0)
  {
    RequestData requestData(this, &mDataProxy);
    requestData.setRequestType(RequestType::GetValues);
    requestData.setRequestVector(mClientRequestMap.keys().toVector());

    mDataProxy.requestData(requestData);
  }
}

//--------------------------------------------------------------------------------------------------------
void DataClientManager::requestCommand(const Request commandRequest, const QString& commandValue)
{
  QStringList valueList;
  RequestData requestData(this, &mDataProxy);
  requestData.setRequestType(RequestType::Command);
  requestData.appendRequest(commandRequest);
  valueList.append(commandValue);
  requestData.appendValueList(valueList);

  mDataProxy.requestData(requestData);
}

//--------------------------------------------------------------------------------------------------------
void DataClientManager::requestSaveData(const Request request, const QString& requestValue)
{
  QStringList valueList;
  RequestData requestData(this, &mDataProxy);
  requestData.setRequestType(RequestType::SetValues);
  requestData.appendRequest(request);
  valueList.append(requestValue);
  requestData.appendValueList(valueList);

  mDataProxy.requestData(requestData);
}

//--------------------------------------------------------------------------------------------------------
// Replies from the DataProxy
//--------------------------------------------------------------------------------------------------------
void DataClientManager::newValueReceived(const RequestData &requestData)
{
    const RequestVector &requestVector   = requestData.requestVector();
    const StringMatrix  &dataValueMatrix = requestData.valueMatrix();

    for (int i = 0; i < requestVector.size(); ++i)
    {
        ClientVector* clientVector = &mClientRequestMap[requestVector.at(i)];

        for (int i = 0; i < clientVector->size(); ++i)
        {
          clientVector->at(i)->setValueList(requestVector.at(i).requestCmd, dataValueMatrix.at(i));
        }
    }
}

//--------------------------------------------------------------------------------------------------------
void DataClientManager::newStatusReceived(const RequestData &requestData)
{
    const RequestVector &requestVector   = requestData.requestVector();
    const StringMatrix  &dataValueMatrix = requestData.valueMatrix();

    for (int i = 0; i < requestVector.size(); ++i)
    {
        ClientVector* clientVector = &mClientRequestMap[requestVector.at(i)];

        for (int i = 0; i < clientVector->size(); ++i)
        {
          clientVector->at(i)->setValueList(requestVector.at(i).requestCmd, dataValueMatrix.at(i));
        }
    }
}
