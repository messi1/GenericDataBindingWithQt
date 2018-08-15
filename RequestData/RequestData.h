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

#include <QList>
#include <QStringList>
#include "RequestCommand.h"

class IDataClientManager;
class IDataProxy;

using StringMatrix = QList<QStringList>;


enum class RequestType
{
  GetValues,
  SetValues,
  Command
};

class RequestData
{
public:
  RequestData()=default;
  RequestData(IDataClientManager* dataManager, IDataProxy* dataProxy);

  void setDataManager(IDataClientManager* dataManager);
  IDataClientManager* dataManager() const;

  void setDataProxy(IDataProxy* dataProxy);
  IDataProxy*   dataProxy() const;

  void setRequestCmdVector(RequestCmdVector requestCmdVector);
  const RequestCmdVector &requestCmdVector() const;
  void appendRequestCommand(RequestCmd command);

  void setValueMatrix(const StringMatrix& stringMatrix);
  void appendValueList(const QStringList& valueList);
  const StringMatrix &valueMatrix() const;

  void setRangeMatrix(const StringMatrix& rangeList);
  void appendRangeList(const QStringList& rangeList);
  const StringMatrix &rangeMatrix() const;

  void setErrorMatrix(const StringMatrix& errorMatrix);
  void appendErrorList(const QStringList& errorList);
  const StringMatrix &errorMatrix() const;
  void clearAllData();

  bool operator==(const RequestData& obj) const;

  RequestType requestType() const;
  void setRequestType(const RequestType &requestType);

  bool withRange() const;
  void setWithRange(bool withRange);

  int compartmentId() const;
  void setCompartmentId(int compartmentId);

private:
  IDataClientManager* mCallerManager = nullptr;
  IDataProxy*         mCallerProxy   = nullptr;

  RequestCmdVector    mRequestCmdVector;
  StringMatrix        mValueMatrix;
  StringMatrix        mRangeMatrix;
  StringMatrix        mErrorMatrix;
  bool                mWithRange     = false;
  RequestType         mRequestType   = RequestType::GetValues;
  int                 mCompartmentId = 0;
};

//-------------------------------------------------------------------------------------------------
// Serializer/Deserializer for RequestData Type
//-------------------------------------------------------------------------------------------------

QDataStream& operator<<(QDataStream& out, const RequestData& RequestData);
QDataStream& operator>>(QDataStream&  in,       RequestData& RequestData);
QDataStream &operator<<(QDataStream& out, const RequestCmd&  enumValue);
QDataStream &operator>>(QDataStream&  in,       RequestCmd&  enumValue);
#endif // REQUEST_DATA_H
