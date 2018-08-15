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
void DataClientManager::registerClient(const RequestCmd requestCmd, IDataClient* dataClient)
{
  if(dataClient)
  {
    if(mClientRequestMap.contains(requestCmd))
    {
      if(mClientRequestMap[requestCmd].contains(dataClient) == false )
        mClientRequestMap[requestCmd].append(dataClient);
      else
        qDebug() << "registerValue(): Could register client because it is already registered ";
    }
    else
    {
      mClientRequestMap.insert(requestCmd, ClientVector{dataClient});
    }
  }
}

//--------------------------------------------------------------------------------------------------------
void DataClientManager::deregisterClient(const RequestCmd requestCmd, IDataClient* dataClient)
{
  if(dataClient)
  {
    if(mClientRequestMap.contains(requestCmd))
    {
        bool isContaining = mClientRequestMap[requestCmd].contains(dataClient) ;


      if(isContaining)
      {
        mClientRequestMap[requestCmd].removeAll(dataClient);

        if(mClientRequestMap[requestCmd].count() == 0)
            mClientRequestMap.remove(requestCmd);
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
void DataClientManager::changeRegisteredRequestCmd(IDataClient* dataClient, const RequestCmd oldRequestId, const RequestCmd newRequestId)
{
  if(dataClient)
  {
    deregisterClient(oldRequestId, dataClient);
    registerClient(newRequestId, dataClient);
  }
}

//--------------------------------------------------------------------------------------------------------
const RequestCmdVector DataClientManager::allRequestCmdOfAClient(IDataClient* dataClient) const
{
    RequestCmdVector cmdVector;

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
void DataClientManager::requestGetClientData(IDataClient* dataClient, const RequestCmd requestCmd, bool withRange)
{
  if( dataClient)
  {
    RequestData requestData(this, &mDataProxy);
    // TODO: Add dataClient to the requestData as return path for special single request, like timer based requests.
    requestData.appendRequestCommand(requestCmd);
    requestData.setRequestType(RequestType::GetValues);
    requestData.setWithRange(withRange);

    mDataProxy.requestData(requestData);
  }
}

//--------------------------------------------------------------------------------------------------------
void DataClientManager::requestGetAllClientData(bool withRange)
{
  if(mClientRequestMap.size() > 0)
  {
    RequestData requestData(this, &mDataProxy);
    requestData.setRequestType(RequestType::GetValues);
    requestData.setWithRange(withRange);
    requestData.setRequestCmdVector(mClientRequestMap.keys().toVector());

    mDataProxy.requestData(requestData);
  }
}

//--------------------------------------------------------------------------------------------------------
void DataClientManager::requestCommand(const RequestCmd commandName, const QString& commandValue)
{
  QStringList valueList;
  RequestData requestData(this, &mDataProxy);
  requestData.setRequestType(RequestType::Command);
  requestData.appendRequestCommand(commandName);
  valueList.append(commandValue);
  requestData.appendValueList(valueList);

  mDataProxy.requestData(requestData);
}

//--------------------------------------------------------------------------------------------------------
void DataClientManager::requestSaveData(const RequestCmd requestCmd, const QString& requestValue)
{
  QStringList valueList;
  RequestData requestData(this, &mDataProxy);
  requestData.setRequestType(RequestType::SetValues);
  requestData.appendRequestCommand(requestCmd);
  valueList.append(requestValue);
  requestData.appendValueList(valueList);

  mDataProxy.requestData(requestData);
}

//--------------------------------------------------------------------------------------------------------
// Replies from the DataProxy
//--------------------------------------------------------------------------------------------------------
void DataClientManager::newValueReceived(const RequestData &requestData)
{
    const RequestCmdVector &RequestCmdVector = requestData.requestCmdVector();
    const StringMatrix               &dataValueMatrix  = requestData.valueMatrix();

    for (int i = 0; i < RequestCmdVector.size(); ++i)
    {
        ClientVector* clientVector = &mClientRequestMap[RequestCmdVector.at(i)];

        for (int i = 0; i < clientVector->size(); ++i)
        {
          clientVector->at(i)->setValueList(RequestCmdVector.at(i), dataValueMatrix.at(i));
        }
    }
}

//--------------------------------------------------------------------------------------------------------
void DataClientManager::newStatusReceived(const RequestData &requestData)
{
    const RequestCmdVector &RequestCmdVector = requestData.requestCmdVector();
    const StringMatrix               &dataValueMatrix  = requestData.valueMatrix();

    for (int i = 0; i < RequestCmdVector.size(); ++i)
    {
        ClientVector* clientVector = &mClientRequestMap[RequestCmdVector.at(i)];

        for (int i = 0; i < clientVector->size(); ++i)
        {
          clientVector->at(i)->setValueList(RequestCmdVector.at(i), dataValueMatrix.at(i));
        }
    }
}
