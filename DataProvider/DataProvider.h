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
#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H

#include <QObject>
#include "IDataProvider.h"

class RequestData;
class IConnector;


class DataProvider : public QObject, public IDataProvider
{
  Q_OBJECT
  Q_INTERFACES(IDataProvider)

public:
    explicit DataProvider( IConnector& connector, QObject *parent=nullptr);

public slots:
    void requestData(const RequestData& requestData) override;

private:
    IConnector& mDataConnector;
};

#endif // DATAPROVIDER_H

