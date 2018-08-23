/*
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
#include <QThread>
#include "DataBinding/IDataClientManager.h"
#include "DataProxy.h"
#include "IDataProvider.h"
#include "RequestData/RequestData.h"


//--------------------------------------------------------------------------------------------------------
DataProxy::DataProxy(IDataProvider &dataProvider, QObject *parent)
: QObject(parent),
  mDataProvider(dataProvider)
{
  setObjectName("Dataproxy");
  connect(this, SIGNAL(sigRequestData(const RequestData &)), dynamic_cast<QObject*>(&mDataProvider), SLOT(requestData(const RequestData &)), Qt::QueuedConnection);
  connect(this, &DataProxy::sigResponseData, this, &DataProxy::responseReceived, Qt::QueuedConnection);
}

//--------------------------------------------------------------------------------------------------------
void DataProxy::requestData(const RequestData &requestData)
{
    {
      emit sigRequestData(requestData);
    }
}

//--------------------------------------------------------------------------------------------------------
// Received data from dataThread to the main thread and forward it to the dataClientManager.
//--------------------------------------------------------------------------------------------------------
void DataProxy::responseReceived(const RequestData& requestData)
{
  if(requestData.dataManager())
  {
    requestData.dataManager()->newValueReceived(requestData);
  }
}


