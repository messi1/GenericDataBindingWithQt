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
#ifndef DATACLIENT_H
#define DATACLIENT_H

#include <QString>

#include "IDataClient.h"


class IDataClientManager;

class DataClient : public IDataClient
{
public:
    DataClient() = delete;
    explicit DataClient(IDataClientManager& dataClientManager);
    virtual ~DataClient() = default;

    void registerRequestCmd(const RequestCmd requestCmd);
    void changeRegisteredRequestCmd(const RequestCmd oldRequestCmd, const RequestCmd newRequestCmd);
    void deregisterRequestCmd(const RequestCmd requestCmd);
    void deregisterClient();

    void requestGetData(const RequestCmd requestCmd,  bool withRange = false, quint8 contextId = 0);
    void requestSaveData(const RequestCmd requestCmd, const QString& requestValue);
    virtual void setValueList( const Request& request, const QStringList& responseValueList,
                               const QStringList& responseRangeList)override = 0;
    virtual void setAccessRights(const QString& accessRights)override = 0;
    virtual void setErrorList(const Request& request, const QStringList& responseErrorList)override = 0;
    virtual void refresh()override = 0;

protected:
    IDataClientManager& mDataClientManager;
};

#endif // DATACLIENT_H
