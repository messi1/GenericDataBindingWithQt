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

#ifndef TESTREQUESTVALUES_H
#define TESTREQUESTVALUES_H

#include <QStringList>
#include "RequestResponseData/RequestCommand.h"
#include "RequestResponseData/RequestData.h"
#include "RequestResponseData/ResponseData.h"

using TestRequestList = QList<Request>;

void fillRequestData(RequestData& data);
RequestData createRequestData(const TestRequestList& requestList);

struct TestRequestValues
{
    const Request request1{RequestCmd::WlanList,  true};
    const Request request2{RequestCmd::WlanState, false, 1};
    const Request request3{RequestCmd::Language,  true , 2};

    const Request request4{RequestCmd::WlanList,  false, 3};
    const Request request5{RequestCmd::WlanState, true,  4};
    const Request request6{RequestCmd::Language,  false, 5};

    const QList<Request> requestList{ request1, request2, request3, request4, request5, request6 };

    RequestData requestData1 = createRequestData({request1, request2, request3});
    RequestData requestData2 = createRequestData({request4, request5, request6});

    QStringList valueList1 = {"1", "2", "3"};
    QStringList valueList2 = {"5", "6", "7", "8"};
};

#endif // TESTREQUESTVALUES_H
