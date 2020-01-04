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
#include "ResponseData.h"



bool operator==(const ResponseValue& stringMatrix1, const ResponseValue& stringMatrix2)
{
    return (stringMatrix1.valueList == stringMatrix2.valueList &&
            stringMatrix1.rangeList == stringMatrix2.rangeList &&
            stringMatrix1.errorList == stringMatrix2.errorList );
}

//-------------------------------------------------------------------------------------------------
ResponseData::ResponseData(const DataClientMangerWeakPtr &dataManager, const DataProxyWeakPtr &dataProxy)
  : mCallerManager(dataManager),
    mCallerProxy(dataProxy)
{}

//-------------------------------------------------------------------------------------------------
void ResponseData::setDataClientManager(const DataClientMangerWeakPtr& dataManager)
{
  mCallerManager = dataManager;
}

//-------------------------------------------------------------------------------------------------
void ResponseData::setDataProxy(const DataProxyWeakPtr& dataProxy)
{
  mCallerProxy = dataProxy;
}

//-------------------------------------------------------------------------------------------------
DataClientMangerWeakPtr ResponseData::dataClientManager() const
{
  return mCallerManager;
}

//-------------------------------------------------------------------------------------------------
DataProxyWeakPtr ResponseData::dataProxy() const
{
    return mCallerProxy;
}

//-------------------------------------------------------------------------------------------------
QString ResponseData::accessRights(const Request &request) const
{
    bool res = mResponseMap.contains(request);
    if (res)
    {
        return mResponseMap[request].accessRights;
    }

    return QString();
}

//-------------------------------------------------------------------------------------------------
bool ResponseData::valueList(const Request &request, QStringList &valueList)
{
    bool res = mResponseMap.contains(request);
    if(res)
        valueList = mResponseMap[request].valueList;

    return res;
}

//-------------------------------------------------------------------------------------------------
bool ResponseData::rangeList(const Request &request, QStringList &rangeList)
{
    bool res = mResponseMap.contains(request);
    if(res)
        rangeList = mResponseMap[request].rangeList;

    return res;
}

//-------------------------------------------------------------------------------------------------
bool ResponseData::errorList(const Request &request, QStringList &errorList)
{
    bool res = mResponseMap.contains(request);
    if(res)
        errorList = mResponseMap[request].errorList;

    return res;
}
//-------------------------------------------------------------------------------------------------
void ResponseData::setValueList(const Request &request, const QStringList &valueList)
{
    if(mResponseMap.contains(request))
    {
      mResponseMap[request].valueList = valueList;
    }
    else
        mResponseMap[request] = {valueList, QStringList(), QStringList(), ""};
}

//-------------------------------------------------------------------------------------------------
void ResponseData::setRangeList(const Request &request, const QStringList &rangeList)
{
    if(mResponseMap.contains(request))
    {
      mResponseMap[request].rangeList = rangeList;
    }
    else
        mResponseMap[request] = {QStringList(), rangeList, QStringList(), ""};
}

//-------------------------------------------------------------------------------------------------
void ResponseData::setErrorList(const Request &request, const QStringList &errorList)
{
    if(mResponseMap.contains(request))
    {
      mResponseMap[request].errorList = errorList;
    }
    else
        mResponseMap[request] = {QStringList(), QStringList(), errorList, ""};
}

//-------------------------------------------------------------------------------------------------
void ResponseData::addResponse(const Request& request, const QString& accessRights)
{
  ResponseValue stringMatrix;
  stringMatrix.accessRights = accessRights;

  mResponseMap.insert(request, stringMatrix);
}

//-------------------------------------------------------------------------------------------------
void ResponseData::addResponse(const Request& request, const QStringList &valueList, const QString& accessRights)
{
  ResponseValue stringMatrix;
  stringMatrix.valueList    = valueList;
  stringMatrix.accessRights = accessRights;

  mResponseMap.insert(request, stringMatrix);
}

//-------------------------------------------------------------------------------------------------
void ResponseData::addResponse(const Request& request, const QStringList &valueList, const QStringList &rangeList, const QString& accessRights)
{
  ResponseValue stringMatrix;
  stringMatrix.valueList    = valueList;
  stringMatrix.rangeList    = rangeList;
  stringMatrix.accessRights = accessRights;

  mResponseMap.insert(request, stringMatrix);
}

//-------------------------------------------------------------------------------------------------
void ResponseData::addResponse(const Request& request, const QStringList &valueList, const QStringList &rangeList, const QStringList &errorList, const QString& accessRights)
{
  ResponseValue stringMatrix;
  stringMatrix.valueList    = valueList;
  stringMatrix.rangeList    = rangeList;
  stringMatrix.errorList    = errorList;
  stringMatrix.accessRights = accessRights;

  mResponseMap.insert(request, stringMatrix);
}

//-------------------------------------------------------------------------------------------------
void ResponseData::setResponseMap(const ResponseMap &requestMap)
{
  mResponseMap = requestMap;
}

//-------------------------------------------------------------------------------------------------
const ResponseMap &ResponseData::responseMap() const
{
  return mResponseMap;
}

//-------------------------------------------------------------------------------------------------
void ResponseData::clearAllData()
{
    QMapIterator<Request, ResponseValue> it(mResponseMap);

    while (it.hasNext())
    {
        it.next();
        mResponseMap[it.key()].valueList.clear();
        mResponseMap[it.key()].rangeList.clear();
        mResponseMap[it.key()].errorList.clear();
    }
}

//-------------------------------------------------------------------------------------------------
RequestType ResponseData::requestType() const
{
  return mRequestType;
}

//-------------------------------------------------------------------------------------------------
void ResponseData::setRequestType(const RequestType &requestType)
{
  mRequestType = requestType;
}

//-------------------------------------------------------------------------------------------------
bool ResponseData::operator==(const ResponseData& obj) const
{
    return (obj.requestType()  == this->requestType()       &&
       obj.dataClientManager() == this->dataClientManager() &&
       obj.dataProxy()         == this->dataProxy()         &&
       obj.responseMap()       == this->responseMap());
}

//-------------------------------------------------------------------------------------------------
// Serializer/deserializer operators
//-------------------------------------------------------------------------------------------------

QDataStream &operator<<(QDataStream &out, const ResponseValue &stringMatrix)
{
  out << stringMatrix.valueList << stringMatrix.rangeList << stringMatrix.errorList;
  return out;
}
//-------------------------------------------------------------------------------------------------
QDataStream &operator>>(QDataStream &in, ResponseValue &stringMatrix)
{
  in >> stringMatrix.valueList >> stringMatrix.rangeList >> stringMatrix.errorList;
  return in;
}

//-------------------------------------------------------------------------------------------------
QDataStream &operator<<(QDataStream &out, const ResponseData &responseData)
{
  out << responseData.responseMap();
  return out;
}

//-------------------------------------------------------------------------------------------------
QDataStream &operator>>(QDataStream &in,  ResponseData &responseData)
{
  ResponseMap responseMap;
  ResponseValue valueMatrix;
  ResponseValue rangeMatrix;
  ResponseValue errorMatrix;
  in >> responseMap;

  responseData.setResponseMap(responseMap);

  return in;
}
