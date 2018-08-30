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

#ifndef TESTVALUES_H
#define TESTVALUES_H

#include <QStringList>
#include "RequestData/RequestCommand.h"
#include "RequestData/RequestData.h"

using TestRequestList    = QList<Request>;
using TestStringListList = QList<QStringList>;

RequestData fillRequestData(const TestRequestList& requestList);
RequestData fillRequestData(const TestRequestList& requestList, const TestStringListList& valueList);
RequestData fillRequestData(const TestRequestList& requestList, const TestStringListList& valueList, const TestStringListList& rangeList);
RequestData fillRequestData(const TestRequestList& requestList, const TestStringListList& valueList, const TestStringListList& rangeList, const TestStringListList& errorList);

struct TestValues
{
    const Request request1{RequestCmd::WlanList,  true};
    const Request request2{RequestCmd::WlanState, false, 1};
    const Request request3{RequestCmd::Language,  true , 2};

    const Request request4{RequestCmd::WlanList,  false, 3};
    const Request request5{RequestCmd::WlanState, true,  4};
    const Request request6{RequestCmd::Language,  false, 5};

    const QList<Request> requestList{ request1, request2, request3, request4, request5, request6 };

    const QStringList valueList1 = {"5","10","20","" };
    const QStringList valueList2 = {"7","44","33","" };
    const QStringList valueList3 = {"87","23","","99"};

    const QStringList rangeList1 = {"1-4","10-20","20-100","" };
    const QStringList rangeList2 = {"7-9","44-50","33-37","" };
    const QStringList rangeList3 = {"87-92","23-45","","99-100"};

    const QStringList errorList1 = {"error 5","error 10","error 20","" };
    const QStringList errorList2 = {"error 7","error 44","error 33","" };
    const QStringList errorList3 = {"error 87","error 23","","error 99"};

    RequestData requestData1  = fillRequestData({request1, request2, request3});
    RequestData requestData2  = fillRequestData({request4, request5, request6});

    RequestData responseData1 = fillRequestData({request1, request2, request3},
                                                {valueList1, valueList2,valueList3},
                                                {rangeList1, rangeList2}, {errorList1});
    RequestData responseData2 = fillRequestData({request4, request5, request6},
                                                {valueList1, valueList2,valueList3},
                                                {rangeList1, rangeList2}, {errorList1});
};



#endif // TESTVALUES_H
