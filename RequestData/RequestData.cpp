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
    return (stringMatrix1.mValueList == stringMatrix2.mValueList &&
            stringMatrix1.mRangeList == stringMatrix2.mRangeList &&
            stringMatrix1.mErrorList == stringMatrix2.mErrorList );
}

//-------------------------------------------------------------------------------------------------
RequestData::RequestData(IDataClientManager *dataManager, IDataProxy *dataProxy)
  : mCallerManager(dataManager),
    mCallerProxy(dataProxy)
{}

//-------------------------------------------------------------------------------------------------
void RequestData::setDataManager(IDataClientManager* dataManager)
{
  mCallerManager = dataManager;
}

//-------------------------------------------------------------------------------------------------
void RequestData::setDataProxy(IDataProxy* dataProxy)
{
  mCallerProxy = dataProxy;
}

//-------------------------------------------------------------------------------------------------
IDataClientManager *RequestData::dataManager() const
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
        valueList = mRequestMap[request].mValueList;

    return res;
}

//-------------------------------------------------------------------------------------------------
bool RequestData::rangeList(const Request &request, QStringList &rangeList)
{
    bool res = mRequestMap.contains(request);
    if(res)
        rangeList = mRequestMap[request].mRangeList;

    return res;
}

//-------------------------------------------------------------------------------------------------
bool RequestData::errorList(const Request &request, QStringList &errorList)
{
    bool res = mRequestMap.contains(request);
    if(res)
        errorList = mRequestMap[request].mErrorList;

    return res;
}

//-------------------------------------------------------------------------------------------------
void RequestData::setValueList(const Request &request, const QStringList &valueList)
{
    if(mRequestMap.contains(request))
    {
      mRequestMap[request].mValueList = valueList;
    }
    else
        mRequestMap[request] = {valueList, QStringList(), QStringList()};
}

//-------------------------------------------------------------------------------------------------
void RequestData::setRangeList(const Request &request, const QStringList &rangeList)
{
    if(mRequestMap.contains(request))
    {
      mRequestMap[request].mRangeList = rangeList;
    }
    else
        mRequestMap[request] = {QStringList(), rangeList, QStringList()};
}

//-------------------------------------------------------------------------------------------------
void RequestData::setErrorList(const Request &request, const QStringList &errorList)
{
    if(mRequestMap.contains(request))
    {
      mRequestMap[request].mErrorList = errorList;
    }
    else
        mRequestMap[request] = {QStringList(), QStringList(), errorList};
}

//-------------------------------------------------------------------------------------------------
void RequestData::appendRequestList(const RequestVector &requestVector)
{
    for(int i = 0; i < requestVector.count(); ++i)
    {
        mRequestMap[requestVector.at(i)] = {};
    }
}

//-------------------------------------------------------------------------------------------------
void RequestData::appendRequest(const Request& request)
{
    if(mRequestMap.contains(request) == false)
        mRequestMap[request] = RequestDataMatrix();
}

//-------------------------------------------------------------------------------------------------
void RequestData::appendRequest(const Request& request, const QStringList &valueList)
{
    if(mRequestMap.contains(request) == false)
    {
        RequestDataMatrix stringMatrix;
        stringMatrix.mValueList = valueList;

        mRequestMap[request] = stringMatrix;
    }
}

//-------------------------------------------------------------------------------------------------
void RequestData::appendRequest(const Request& request, const QStringList &valueList, const QStringList &rangeList)
{
    if(mRequestMap.contains(request) == false)
    {
        RequestDataMatrix stringMatrix;
        stringMatrix.mValueList = valueList;
        stringMatrix.mRangeList = rangeList;

        mRequestMap[request] = stringMatrix;
    }
}

//-------------------------------------------------------------------------------------------------
void RequestData::appendRequest(const Request& request, const QStringList &valueList, const QStringList &rangeList, const QStringList &errorList)
{
    if(mRequestMap.contains(request) == false)
    {
        RequestDataMatrix stringMatrix;
        stringMatrix.mValueList = valueList;
        stringMatrix.mRangeList = rangeList;
        stringMatrix.mErrorList = errorList;

        mRequestMap[request] = stringMatrix;
    }
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
        mRequestMap[it.key()].mValueList.clear();
        mRequestMap[it.key()].mRangeList.clear();
        mRequestMap[it.key()].mErrorList.clear();
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
       obj.dataManager()       == this->dataManager() &&
       obj.dataProxy()         == this->dataProxy()   &&
       obj.requestMap()        == this->requestMap());
}

//-------------------------------------------------------------------------------------------------
// Serializer/deserializer operators
//-------------------------------------------------------------------------------------------------

QDataStream &operator<<(QDataStream &out, const RequestDataMatrix &stringMatrix)
{
  out << stringMatrix.mValueList << stringMatrix.mRangeList << stringMatrix.mErrorList;
  return out;
}
//-------------------------------------------------------------------------------------------------
QDataStream &operator>>(QDataStream &in, RequestDataMatrix &stringMatrix)
{
  in >> stringMatrix.mValueList >> stringMatrix.mRangeList >> stringMatrix.mErrorList;
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
  out << bla << request.withRange << request.contexId;
  return out;
}

//-------------------------------------------------------------------------------------------------
QDataStream &operator>>(QDataStream& in, Request& request)
{
    unsigned int tmp;
    in >> tmp >> request.withRange >> request.contexId;
    request.requestCmd = static_cast<RequestCmd>(tmp);
    return in;
}

