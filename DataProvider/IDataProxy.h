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
#ifndef __IDATA_PROXY
#define __IDATA_PROXY

#include <QObject>

class RequestData;

class IDataProxy
{
public:
  virtual ~IDataProxy()=default;
  virtual void requestData(const RequestData& requestData) = 0;

  signals:
    virtual void sigRequestData(const RequestData& requestData)  = 0;
    virtual void sigResponseData(const RequestData& requestData) = 0;
};

Q_DECLARE_INTERFACE(IDataProxy, "IDataProxy")

#endif // __IDATA_PROXY
