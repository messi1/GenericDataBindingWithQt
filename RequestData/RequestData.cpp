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

#include <type_traits>


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
void RequestData::setRequestVector(RequestVector requestVector)
{
  mRequestVector = requestVector;
}

//-------------------------------------------------------------------------------------------------
const  RequestVector &RequestData::requestVector() const
{
  return mRequestVector;
}

//-------------------------------------------------------------------------------------------------
void RequestData::appendRequest(Request command)
{
  mRequestVector.append(command);
}

//-------------------------------------------------------------------------------------------------
void RequestData::setValueMatrix(const StringMatrix &stringMatrix)
{
  mValueMatrix = stringMatrix;
}

//-------------------------------------------------------------------------------------------------
void RequestData::appendValueList(const QStringList &valueList)
{
  mValueMatrix.append(valueList);
}

//-------------------------------------------------------------------------------------------------
const StringMatrix &RequestData::valueMatrix() const
{
    return mValueMatrix;
}

//-------------------------------------------------------------------------------------------------
void RequestData::setRangeMatrix(const StringMatrix &rangeMatrix)
{
  mRangeMatrix = rangeMatrix;
}

//-------------------------------------------------------------------------------------------------
const StringMatrix &RequestData::rangeMatrix() const
{
  return mRangeMatrix;
}

//-------------------------------------------------------------------------------------------------
void RequestData::appendRangeList(const QStringList &rangeList)
{
  mRangeMatrix.append(rangeList);
}

//-------------------------------------------------------------------------------------------------
void RequestData::setErrorMatrix(const StringMatrix &errorMatrix)
{
  mErrorMatrix = errorMatrix;
}

//-------------------------------------------------------------------------------------------------
const StringMatrix &RequestData::errorMatrix() const
{
  return mErrorMatrix;
}

//-------------------------------------------------------------------------------------------------
void RequestData::appendErrorList(const QStringList &errorList)
{
  mErrorMatrix.append(errorList);
}

//-------------------------------------------------------------------------------------------------
void RequestData::clearAllData()
{
  mRequestVector.clear();
  mValueMatrix.clear();
  mRangeMatrix.clear();
  mErrorMatrix.clear();
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
  if(this == &obj)
    return true;
  else
    return false;
}

//-------------------------------------------------------------------------------------------------
// Serializer/deserializer operators
//-------------------------------------------------------------------------------------------------
QDataStream &operator<<(QDataStream &out, const RequestData &requestData)
{
  out << requestData.requestVector() << requestData.valueMatrix() << requestData.rangeMatrix() << requestData.errorMatrix();

  return out;
}

//-------------------------------------------------------------------------------------------------
QDataStream &operator>>(QDataStream &in,  RequestData &requestData)
{
  RequestVector requestVector;
  StringMatrix valueMatrix;
  StringMatrix rangeMatrix;
  StringMatrix errorMatrix;
  in >> requestVector >> valueMatrix >> rangeMatrix >> errorMatrix;

  requestData.setRequestVector(requestVector);
  requestData.setValueMatrix(valueMatrix);
  requestData.setRangeMatrix(rangeMatrix);
  requestData.setErrorMatrix(errorMatrix);

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


