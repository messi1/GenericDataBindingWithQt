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
#include <QDataStream>
#include "DataBinding/IDataClientManager.h"
#include "DataProvider/IDataProxy.h"
#include "RequestData.h"



//-------------------------------------------------------------------------------------------------
RequestData::RequestData(IDataClientManager *dataManager, IDataProxy *dataProxy)
  : mCallerManager(dataManager),
    mCallerProxy(dataProxy)
{}

//-------------------------------------------------------------------------------------------------
void RequestData::setDataClientManager(IDataClientManager* dataManager)
{
  mCallerManager = dataManager;
}

//-------------------------------------------------------------------------------------------------
void RequestData::setDataProxy(IDataProxy* dataProxy)
{
  mCallerProxy = dataProxy;
}

//-------------------------------------------------------------------------------------------------
IDataClientManager *RequestData::dataClientManager() const
{
  return mCallerManager;
}

//-------------------------------------------------------------------------------------------------
IDataProxy *RequestData::dataProxy() const
{
  return mCallerProxy;
}

//-------------------------------------------------------------------------------------------------
bool RequestData::valueList(const Request &request, QStringList &valueList)
{
    bool res = mRequestMap.contains(request);
    if(res)
        valueList = mRequestMap[request];

    return res;
}

//-------------------------------------------------------------------------------------------------
void RequestData::setValueList(const Request &request, const QStringList &valueList)
{
    mRequestMap[request] = valueList;
}

//-------------------------------------------------------------------------------------------------
void RequestData::addRequestList(const RequestList &requestList)
{
    for(int i = 0; i < requestList.count(); ++i)
    {
        mRequestMap.insert(requestList.at(i), {});
    }
}
//-------------------------------------------------------------------------------------------------
void RequestData::addRequest(const Request& request)
{
    mRequestMap.insert(request, {});
}
//-------------------------------------------------------------------------------------------------
void RequestData::addRequest(const Request& request, const QStringList &valueList)
{
  mRequestMap.insert(request, valueList);
}

//-------------------------------------------------------------------------------------------------
void RequestData::setRequestMap(const RequestMap &requestMap)
{
  mRequestMap = requestMap;
}

//-------------------------------------------------------------------------------------------------
const RequestMap &RequestData::requestMap() const
{
  return mRequestMap;
}

//-------------------------------------------------------------------------------------------------
void RequestData::clearAllValues()
{
    QMapIterator<Request, QStringList> it(mRequestMap);

    while (it.hasNext()) {
        it.next();
        mRequestMap[it.key()].clear();
    }
}

//-------------------------------------------------------------------------------------------------
void RequestData::clearRequestMap()
{
    mRequestMap.clear();
}

//-------------------------------------------------------------------------------------------------
RequestType RequestData::requestType() const
{
  return mRequestType;
}

//-------------------------------------------------------------------------------------------------
void RequestData::setRequestType(const RequestType &requestType)
{
  mRequestType = requestType;
}

//-------------------------------------------------------------------------------------------------
bool RequestData::operator==(const RequestData& obj) const
{
    return (obj.requestType()  == this->requestType() &&
       obj.dataClientManager() == this->dataClientManager() &&
       obj.dataProxy()         == this->dataProxy()   &&
       obj.requestMap()        == this->requestMap());
}

//-------------------------------------------------------------------------------------------------
// Serializer/deserializer operators
//-------------------------------------------------------------------------------------------------
QDataStream &operator<<(QDataStream &out, const RequestData &requestData)
{
    out << static_cast<typename std::underlying_type<RequestType>::type>(requestData.requestType()) << requestData.requestMap();
    return out;
}

//-------------------------------------------------------------------------------------------------
QDataStream &operator>>(QDataStream &in,  RequestData &requestData)
{
    RequestMap requestMap;
    unsigned int tmp = 0;
    in >> tmp >> requestMap;

    requestData.setRequestType(static_cast<RequestType>(tmp));
    requestData.setRequestMap(requestMap);

    return in;
}

//-------------------------------------------------------------------------------------------------
QDataStream &operator<<(QDataStream& out, const  Request& request)
{
  auto serialized_cmd = static_cast<typename std::underlying_type<RequestCmd>::type>(request.requestCmd);
  out << serialized_cmd << request.withRange << request.contextId;
  return out;
}

//-------------------------------------------------------------------------------------------------
QDataStream &operator>>(QDataStream& in, Request& request)
{
    unsigned int tmp = 0;
    in >> tmp >> request.withRange >> request.contextId;
    request.requestCmd = static_cast<RequestCmd>(tmp);
    return in;
}

