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
#ifndef __IDATA_CLIENT
#define __IDATA_CLIENT

// Cant be class forwarded because of multiple inclusion which generate previous declartion error
#include "RequestData/RequestCommand.h"

class QString;
class QStringList;

class IDataClient
{
public:
    IDataClient() = default;
    virtual ~IDataClient() = default;
    virtual void setValueList( const Request& request, const QStringList& responseValueList,
                               const QStringList& responseRangeList, const QStringList& responseErrorList) = 0;
    virtual void setStatusList(const Request& request,
                               const QStringList& responseStatusList, const QStringList& responseErrorList) = 0;
    virtual void refresh() = 0;
};

#endif // __IDATA_CLIENT
