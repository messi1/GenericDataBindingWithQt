/*
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
#include <QObject>
#include <QThread>

#include "IDataProxy.h"
#include "DataProvider.h"
#include "RequestData/RequestData.h"
#include "RequestBroker/IConnector.h"


//--------------------------------------------------------------------------------------------------------
DataProvider::DataProvider (IConnector& connector, QObject *parent) :
    QObject(parent),
    mDataConnector(connector)
{
  qRegisterMetaType<RequestData>("RequestData");
  setObjectName("DataProvider");
}

//--------------------------------------------------------------------------------------------------------
void DataProvider::requestData(const RequestData& requestData)
{
  RequestData responseData;
  bool lRes = false;

  lRes = mDataConnector.requestData(requestData, responseData);

  if(!lRes)
  {
    qCritical() << "requestData failed.";
  }

  // Answer received and send it back to the requested proxy
  if(requestData.dataProxy())
  {
    emit requestData.dataProxy()->sigResponseData(responseData);
  }
  else
  {
    qCritical() << "No Proxy were installed. The data cannot be returned to the caller";
    Q_ASSERT(requestData.dataProxy());
//    abort();
  }
}

