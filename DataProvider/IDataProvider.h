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
#ifndef IDATA_PROVIDER
#define IDATA_PROVIDER

#include <QObject>

class RequestData;

class IDataProvider
{
public:
    virtual ~IDataProvider() = default;

public slots:
    virtual void requestData(const RequestData& requestData) = 0;
};

Q_DECLARE_INTERFACE(IDataProvider, "IDataProvider")

#endif // IDATA_PROVIDER
