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
#ifndef IDATA_CLIENT_MANAGER
#define IDATA_CLIENT_MANAGER

// Cant be class forwarded because of multiple inclusion which generate previous declartion error
#include "RequestResponseData/RequestData.h"
#include "RequestResponseData/ResponseData.h"
#include "RequestResponseData/RequestCommand.h"

class IDataClient;
class IDataProxy;

class IDataClientManager
{
public:
    virtual ~IDataClientManager() = default;
    virtual void registerClient(const Request& request, IDataClient* dataClient) = 0;
    virtual void deregisterClient(const Request& request, IDataClient* dataClient) = 0;
    virtual void deregisterAllClient(IDataClient* dataClient) = 0;
    virtual void changeRegisteredRequest(IDataClient* dataClient, const Request& oldRequestId, const Request& newRequestId) = 0;

    [[nodiscard]] virtual DataProxyWeakPtr dataProxy()  const = 0;
    [[nodiscard]] virtual IDataClientManager* clone() const = 0;

    virtual void requestData(const RequestData &requestData) = 0;
    virtual void requestSaveData(const Request& saveRequest,   const QStringList& valueList) = 0;
    virtual void requestCommand(const Request& commandRequest, const QStringList& valueList) = 0;
    virtual void requestGetClientData(IDataClient* dataClient, const Request& request)       = 0;
    virtual void requestGetAllClientData() = 0;

    virtual void newValueReceived(const ResponseData &requestData)  = 0;
};

#endif // IDATA_CLIENT_MANAGER
