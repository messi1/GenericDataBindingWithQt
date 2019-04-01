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
#ifndef REQUEST_DATA_H
#define REQUEST_DATA_H

#include <QMap>
#include <QStringList>
#include <QWeakPointer>
#include "RequestCommand.h"

class IDataClientManager;
class IDataProxy;

//-------------------------------------------------------------------------------------------------
struct RequestDataMatrix {
    QStringList        valueList;
    QStringList        rangeList;
    QStringList        errorList;
    QString            accessRights;
};
//-------------------------------------------------------------------------------------------------
bool operator==(const RequestDataMatrix& dataMatrix1, const RequestDataMatrix& dataMatrix2);
//-------------------------------------------------------------------------------------------------
using RequestMap          = QMap<Request, RequestDataMatrix>;
using RequestList         = QList<Request>;
using DataProxyWeakPtr    = QWeakPointer<IDataProxy>;
using ClientMangerWeakPtr = QWeakPointer<IDataClientManager>;
//-------------------------------------------------------------------------------------------------

class RequestData
{
public:
  RequestData()=default;
  RequestData(const ClientMangerWeakPtr& dataManager, const DataProxyWeakPtr& dataProxy);
  // TODO: Missing Copy ctor and assignement operator

  void setDataClientManager(const ClientMangerWeakPtr& dataManager);
  ClientMangerWeakPtr dataClientManager() const;

  void setDataProxy(const DataProxyWeakPtr& dataProxy);
  DataProxyWeakPtr   dataProxy() const;

  const QString accessRights(const Request& request) const;

  bool valueList(const Request& request, QStringList &valueList);
  bool rangeList(const Request& request, QStringList& rangeList);
  bool errorList(const Request& request, QStringList& errorList);

  void setValueList(const Request& request, const QStringList& valueList);
  void setRangeList(const Request& request, const QStringList& rangeList);
  void setErrorList(const Request& request, const QStringList& errorList);

  void addRequestList(const RequestList& requestList);
  void addRequest(const Request& request, const QString& accessRights="");
  void addRequest(const Request& request, const QStringList& valueList, const QString& accessRights="");
  void addRequest(const Request& request, const QStringList& valueList, const QStringList& rangeList, const QString& accessRights="");
  void addRequest(const Request& request, const QStringList& valueList, const QStringList& rangeList,
                  const QStringList& errorList, const QString& accessRights="");

  void setRequestMap(const RequestMap& requestMap);
  const RequestMap &requestMap() const;

  void clearAllData();

  bool operator==(const RequestData& obj) const;

  RequestType requestType() const;
  void setRequestType(const RequestType &requestType);

private:
  ClientMangerWeakPtr mManagerToSendResponse;
  DataProxyWeakPtr    mCallerProxy;

  RequestMap  mRequestMap;
  RequestType mRequestType   = RequestType::GetValues;
};

//-------------------------------------------------------------------------------------------------
// Serializer/Deserializer for RequestData Type
//-------------------------------------------------------------------------------------------------
QDataStream& operator<<(QDataStream& out, const RequestDataMatrix& stringMatrix);
QDataStream& operator>>(QDataStream&  in,       RequestDataMatrix& stringMatrix);
QDataStream& operator<<(QDataStream& out, const RequestData& requestData);
QDataStream& operator>>(QDataStream&  in,       RequestData& requestData);
QDataStream &operator<<(QDataStream& out, const Request&  request);
QDataStream &operator>>(QDataStream&  in,       Request&  request);
#endif // REQUEST_DATA_H
