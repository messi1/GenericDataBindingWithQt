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
#ifndef IDATA_CLIENT
#define IDATA_CLIENT

// Cant be class forwarded because of multiple inclusion which generate previous declartion error
#include "RequestResponseData/RequestCommand.h"

class QString;
class QStringList;

class IDataClient
{
public:
    IDataClient() = default;
    virtual ~IDataClient() = default;
    virtual void setValueList( const Request& request, const QStringList& responseValueList,
                               const QStringList& responseRangeList) = 0;
    virtual void setAccessRights(const QString& accessRights) = 0;
    virtual void setErrorList(const Request& request, const QStringList& responseErrorList) = 0;
    virtual void refresh() = 0;
};

#endif // IDATA_CLIENT
