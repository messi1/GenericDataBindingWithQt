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
#include "DataClient.h"
#include "IDataClientManager.h"

#include "RequestData/RequestCommand.h"
#include "RequestData/RequestData.h"

//--------------------------------------------------------------------------------------------------------
DataClient::DataClient(IDataClientManager &dataClientManager)
: mDataClientManager(dataClientManager)
{}


//--------------------------------------------------------------------------------------------------------
void DataClient::registerRequestCmd(const RequestCmd requestCmd)
{
  mDataClientManager.registerClient({requestCmd}, this);
}

//--------------------------------------------------------------------------------------------------------
void DataClient::changeRegisteredRequestCmd(const RequestCmd oldRequestCmd, const RequestCmd newRequestCmd)
{
  mDataClientManager.changeRegisteredRequest( this, {oldRequestCmd}, {newRequestCmd} );
}

//--------------------------------------------------------------------------------------------------------
void DataClient::deregisterClient()
{
  mDataClientManager.deregisterAllClient(this);
}

//--------------------------------------------------------------------------------------------------------
void DataClient::deregisterRequestCmd(const RequestCmd requestCmd)
{
  mDataClientManager.deregisterClient({requestCmd}, this);
}

//--------------------------------------------------------------------------------------------------------
void DataClient::requestGetData(const RequestCmd requestCmd, bool withRange, quint8 contextId)
{
    Request request{requestCmd, withRange, contextId};
  mDataClientManager.requestGetClientData(this, request);
}

//--------------------------------------------------------------------------------------------------------
void DataClient::requestSaveData(const RequestCmd requestCmd, const QString& requestValue)
{
  mDataClientManager.requestSaveData({requestCmd}, requestValue);
}

//--------------------------------------------------------------------------------------------------------
//void DataClient::setValue(const QString& requestName, const QString& requestValue, const QString& requestRange, const int status)
//{
//    qDebug() << "Please reimplement it in your class. :setValue(const QString& requestName, const QString& requestValue, const QString& requestRange, const int status)";
//    qDebug() << "::setValue: Name:" << requestNa{me << " Value:" << requestValue << " Range:" << requestRange << " Status:" << status;
//}



//--------------------------------------------------------------------------------------------------------
//void DataClient::setValue(const QString& requestName, const QString& requestValue)
//{
//    qDebug() << "Please reimplement it in your class. setValue(const QString& requestName, const QString& requestValue)";
//    qDebug() << "::setValue: Name:" << requestName << " Value:" << requestValue;
//}

//--------------------------------------------------------------------------------------------------------
//void DataClient::setStatus(const QString& requestName, const QString& requestError, const int status)
//{
//    qDebug() << "Please reimplement it in your class. setStatus(const QString& requestName, const QString& requestError, const int status)";
//    qDebug() << "::setStatus: Name:" << requestName << " Error:" << requestError  << " Status:" << status;
//}
