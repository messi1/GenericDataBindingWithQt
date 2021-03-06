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

#include "RequestResponseData/RequestCommand.h"
#include "RequestResponseData/RequestData.h"

//--------------------------------------------------------------------------------------------------------
DataClient::DataClient(IDataClientManager &dataClientManager)
: mDataClientManager(dataClientManager)
{}

//--------------------------------------------------------------------------------------------------------
void DataClient::registerRequestCmd(RequestCmd requestCmd)
{
    mDataClientManager.registerClient({requestCmd}, this);
}

//--------------------------------------------------------------------------------------------------------
void DataClient::changeRegisteredRequestCmd(RequestCmd oldRequestCmd, RequestCmd newRequestCmd)
{
    mDataClientManager.changeRegisteredRequest( this, {oldRequestCmd}, {newRequestCmd} );
}

//--------------------------------------------------------------------------------------------------------
void DataClient::deregisterClient()
{
    mDataClientManager.deregisterAllClient(this);
}

//--------------------------------------------------------------------------------------------------------
void DataClient::deregisterRequestCmd(RequestCmd requestCmd)
{
    mDataClientManager.deregisterClient({requestCmd}, this);
}

//--------------------------------------------------------------------------------------------------------
void DataClient::requestGetData(RequestCmd requestCmd, bool withRange, quint8 contextId)
{
    Request request{requestCmd, withRange, contextId};
    mDataClientManager.requestGetClientData(this, request);
}

//--------------------------------------------------------------------------------------------------------
void DataClient::requestSaveData(RequestCmd requestCmd, const QString& requestValue)
{
    mDataClientManager.requestSaveData({requestCmd}, {requestValue});
}
