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
using RequestMap              = QMap<Request, QStringList>;
using RequestList             = QList<Request>;
using DataProxyWeakPtr        = QWeakPointer<IDataProxy>;
using DataClientMangerWeakPtr = QWeakPointer<IDataClientManager>;
//-------------------------------------------------------------------------------------------------

class RequestData
{
public:
  RequestData()=default;
  RequestData(const DataClientMangerWeakPtr& dataManager, const DataProxyWeakPtr& dataProxy);
  void operator=(const RequestData& obj);

  void setDataClientManager(const DataClientMangerWeakPtr& dataManager);
  [[nodiscard]] DataClientMangerWeakPtr dataClientManager() const;

  void setDataProxy(const DataProxyWeakPtr& dataProxy);
  [[nodiscard]] DataProxyWeakPtr   dataProxy() const;

  bool valueList(const Request& request, QStringList &valueList);
  void setValueList(const Request& request, const QStringList& valueList);

  void addRequestList(const RequestList& requestList);
  void addRequest(const Request& request);
  void addRequest(const Request& request, const QStringList& valueList);

  void clearAllValues();

  void clearRequestMap();
  void setRequestMap(const RequestMap &requestMap);
  [[nodiscard]] const RequestMap &requestMap() const;

  bool operator==(const RequestData& obj) const;

  [[nodiscard]] RequestType requestType() const;
  void setRequestType(const RequestType &requestType);

private:
  DataClientMangerWeakPtr mCallerManager;
  DataProxyWeakPtr        mCallerProxy;

  RequestMap  mRequestMap;
  RequestType mRequestType = RequestType::GetValues;
};

//-------------------------------------------------------------------------------------------------
// Serializer/Deserializer for RequestData Type
//-------------------------------------------------------------------------------------------------
QDataStream& operator<<(QDataStream& out, const RequestData& requestData);
QDataStream& operator>>(QDataStream&  in,       RequestData& requestData);
QDataStream &operator<<(QDataStream& out, const Request&  request);
QDataStream &operator>>(QDataStream&  in,       Request&  request);
#endif // REQUEST_DATA_H
