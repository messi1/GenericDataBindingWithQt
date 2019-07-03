

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
#ifndef RESPONSEDATA_H
#define RESPONSEDATA_H

#include <QMap>
#include <QStringList>
#include <QWeakPointer>
#include "RequestCommand.h"

class IDataClientManager;
class IDataProxy;

//-------------------------------------------------------------------------------------------------
struct ResponseValue
{
    QStringList        valueList;
    QStringList        rangeList;
    QStringList        errorList;
    QString            accessRights;
};
//-------------------------------------------------------------------------------------------------
bool operator==(const ResponseValue &dataValue1,
                const ResponseValue &dataValue2);
//-------------------------------------------------------------------------------------------------
using ResponseMap             = QMap<Request, ResponseValue>;
using RequestList             = QList<Request>;
using DataProxyWeakPtr        = QWeakPointer<IDataProxy>;
using DataClientMangerWeakPtr = QWeakPointer<IDataClientManager>;
//-------------------------------------------------------------------------------------------------

class ResponseData
{
public:
    ResponseData()=default;
    ResponseData(IDataClientManager *dataManager, IDataProxy *dataProxy);

    void setDataClientManager(IDataClientManager* dataManager);
    IDataClientManager* dataClientManager() const;

    void setDataProxy(IDataProxy* dataProxy);
    IDataProxy*   dataProxy() const;
    const QString accessRights(const Request& request) const;

    bool valueList(const Request& request, QStringList &valueList);
    bool rangeList(const Request& request, QStringList& rangeList);
    bool errorList(const Request& request, QStringList& errorList);

    void setValueList(const Request& request, const QStringList& valueList);
    void setRangeList(const Request& request, const QStringList& rangeList);
    void setErrorList(const Request& request, const QStringList& errorList);

    void addResponse(const Request& request, const QString& accessRights="");
    void addResponse(const Request& request, const QStringList& valueList, const QString& accessRights="");
    void addResponse(const Request& request, const QStringList& valueList, const QStringList& rangeList, const QString& accessRights="");
    void addResponse(const Request& request, const QStringList& valueList, const QStringList& rangeList,
                    const QStringList& errorList, const QString& accessRights="");

    bool operator==(const ResponseData& obj) const;

    void setResponseMap(const ResponseMap& requestMap);
    const ResponseMap &responseMap() const;

    void clearAllData();

    RequestType requestType() const;
    void setRequestType(const RequestType &requestType);

  private:
    IDataClientManager* mCallerManager = nullptr;
    IDataProxy*         mCallerProxy   = nullptr;

    ResponseMap  mResponseMap;
    RequestType  mRequestType   = RequestType::GetValues;
};

//-------------------------------------------------------------------------------------------------
// Serializer/Deserializer for RequestData Type
//-------------------------------------------------------------------------------------------------
QDataStream &operator<<(QDataStream &out, const ResponseValue &stringMatrix);
QDataStream &operator>>(QDataStream &in, ResponseValue &stringMatrix);
QDataStream& operator<<(QDataStream& out, const ResponseData& requestData);
QDataStream& operator>>(QDataStream&  in,       ResponseData& requestData);


#endif // RESPONSEDATA_H
