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

#ifndef MOCKDATAPROXY_H
#define MOCKDATAPROXY_H

#include <QObject>

#include "DataProvider/IDataProxy.h"

class MockDataProxy: public QObject, public IDataProxy
{
  Q_OBJECT
  Q_INTERFACES(IDataProxy)

public:
  explicit MockDataProxy(QObject* parent=nullptr)
    :QObject(parent)
  {
    setObjectName("MockDataProxy");
  }

  void requestData(const RequestData& requestData) override{ emit sigRequestData(requestData); }

private slots:
  void requestedValuesReceived(const RequestData &/*requestData*/){}
  void requestedStatusReceived(const RequestData &/*requestData*/){}

signals:
  void sigRequestData(const RequestData& requestData) override;
  void sigResponseData(const ResponseData& requestData) override;
};

#endif // MOCKDATAPROXY_H
