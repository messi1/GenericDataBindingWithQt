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



bool operator==(const RequestDataMatrix& stringMatrix1, const RequestDataMatrix& stringMatrix2)
{
    return (stringMatrix1.valueList == stringMatrix2.valueList &&
            stringMatrix1.rangeList == stringMatrix2.rangeList &&
            stringMatrix1.errorList == stringMatrix2.errorList );
}

//-------------------------------------------------------------------------------------------------
RequestData::RequestData(const ClientMangerWeakPtr &dataManager, const DataProxyWeakPtr &dataProxy)
  : mManagerToSendResponse(dataManager),
    mCallerProxy(dataProxy)
{}

//-------------------------------------------------------------------------------------------------
void RequestData::operator=(const RequestData &obj)
{
    this->setDataProxy(obj.dataProxy());
    this->setDataClientManager(obj.dataClientManager());
    this->setRequestMap(obj.requestMap());
    this->setRequestType(obj.requestType());
}

//-------------------------------------------------------------------------------------------------
void RequestData::setDataClientManager(const ClientMangerWeakPtr& dataManager)
{
  mManagerToSendResponse = dataManager;
}

//-------------------------------------------------------------------------------------------------
void RequestData::setDataProxy(const DataProxyWeakPtr& dataProxy)
{
  mCallerProxy = dataProxy;
}

//-------------------------------------------------------------------------------------------------
ClientMangerWeakPtr RequestData::dataClientManager() const
{
    return mManagerToSendResponse;
}

//-------------------------------------------------------------------------------------------------
DataProxyWeakPtr RequestData::dataProxy() const
{
  return mCallerProxy;
}

//-------------------------------------------------------------------------------------------------
const QString RequestData::accessRights(const Request &request) const
{
  return mRequestMap.value(request).accessRights;
}

//-------------------------------------------------------------------------------------------------
bool RequestData::valueList(const Request &request, QStringList &valueList)
{
    bool res = mRequestMap.contains(request);
    if(res)
        valueList = mRequestMap[request].valueList;

    return res;
}

//-------------------------------------------------------------------------------------------------
bool RequestData::rangeList(const Request &request, QStringList &rangeList)
{
    bool res = mRequestMap.contains(request);
    if(res)
        rangeList = mRequestMap[request].rangeList;

    return res;
}

//-------------------------------------------------------------------------------------------------
bool RequestData::errorList(const Request &request, QStringList &errorList)
{
    bool res = mRequestMap.contains(request);
    if(res)
        errorList = mRequestMap[request].errorList;

    return res;
}

//-------------------------------------------------------------------------------------------------
void RequestData::setValueList(const Request &request, const QStringList &valueList)
{
    if(mRequestMap.contains(request))
    {
      mRequestMap[request].valueList = valueList;
    }
    else
        mRequestMap[request] = {valueList, QStringList(), QStringList(), ""};
}

//-------------------------------------------------------------------------------------------------
void RequestData::setRangeList(const Request &request, const QStringList &rangeList)
{
    if(mRequestMap.contains(request))
    {
      mRequestMap[request].rangeList = rangeList;
    }
    else
        mRequestMap[request] = {QStringList(), rangeList, QStringList(), ""};
}

//-------------------------------------------------------------------------------------------------
void RequestData::setErrorList(const Request &request, const QStringList &errorList)
{
    if(mRequestMap.contains(request))
    {
      mRequestMap[request].errorList = errorList;
    }
    else
        mRequestMap[request] = {QStringList(), QStringList(), errorList, ""};
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
void RequestData::addRequest(const Request& request, const QString& accessRights)
{
  RequestDataMatrix stringMatrix;
  stringMatrix.accessRights = accessRights;

  mRequestMap.insert(request, stringMatrix);
}

//-------------------------------------------------------------------------------------------------
void RequestData::addRequest(const Request& request, const QStringList &valueList, const QString& accessRights)
{
  RequestDataMatrix stringMatrix;
  stringMatrix.valueList    = valueList;
  stringMatrix.accessRights = accessRights;

  mRequestMap.insert(request, stringMatrix);
}

//-------------------------------------------------------------------------------------------------
void RequestData::addRequest(const Request& request, const QStringList &valueList, const QStringList &rangeList, const QString& accessRights)
{
  RequestDataMatrix stringMatrix;
  stringMatrix.valueList    = valueList;
  stringMatrix.rangeList    = rangeList;
  stringMatrix.accessRights = accessRights;

  mRequestMap.insert(request, stringMatrix);
}

//-------------------------------------------------------------------------------------------------
void RequestData::addRequest(const Request& request, const QStringList &valueList, const QStringList &rangeList, const QStringList &errorList, const QString& accessRights)
{
  RequestDataMatrix stringMatrix;
  stringMatrix.valueList    = valueList;
  stringMatrix.rangeList    = rangeList;
  stringMatrix.errorList    = errorList;
  stringMatrix.accessRights = accessRights;

  mRequestMap.insert(request, stringMatrix);
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
void RequestData::clearAllData()
{
    QMapIterator<Request, RequestDataMatrix> it(mRequestMap);

    while (it.hasNext()) {
        it.next();
        mRequestMap[it.key()].valueList.clear();
        mRequestMap[it.key()].rangeList.clear();
        mRequestMap[it.key()].errorList.clear();
    }
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

QDataStream &operator<<(QDataStream &out, const RequestDataMatrix &stringMatrix)
{
  out << stringMatrix.valueList << stringMatrix.rangeList << stringMatrix.errorList;
  return out;
}
//-------------------------------------------------------------------------------------------------
QDataStream &operator>>(QDataStream &in, RequestDataMatrix &stringMatrix)
{
  in >> stringMatrix.valueList >> stringMatrix.rangeList >> stringMatrix.errorList;
  return in;
}

//-------------------------------------------------------------------------------------------------
QDataStream &operator<<(QDataStream &out, const RequestData &requestData)
{
  out << requestData.requestMap();

  return out;
}

//-------------------------------------------------------------------------------------------------
QDataStream &operator>>(QDataStream &in,  RequestData &requestData)
{
  RequestMap requestMap;
  RequestDataMatrix valueMatrix;
  RequestDataMatrix rangeMatrix;
  RequestDataMatrix errorMatrix;
  in >> requestMap;

  requestData.setRequestMap(requestMap);

  return in;
}

//-------------------------------------------------------------------------------------------------
QDataStream &operator<<(QDataStream& out, const  Request& request)
{
  unsigned int bla = static_cast<typename std::underlying_type<RequestCmd>::type>(request.requestCmd);
  out << bla << request.withRange << request.contextId;
  return out;
}

//-------------------------------------------------------------------------------------------------
QDataStream &operator>>(QDataStream& in, Request& request)
{
    unsigned int tmp;
    in >> tmp >> request.withRange >> request.contextId;
    request.requestCmd = static_cast<RequestCmd>(tmp);
    return in;
}

