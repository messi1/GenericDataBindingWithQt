#include "TestRequestValues.h"

void fillRequestData(RequestData& data)
{
    const RequestType requestType = RequestType::GetValues;
    QList<Request> requestList{{RequestCmd::BatteryState, true, 3}, {RequestCmd::EthState, false, 1}, {RequestCmd::WlanState, true, 2}};

    const QStringList valueList1{"AA1","BB1","CC1"};
    const QStringList valueList2{"AA2","BB2","CC2"};
    const QStringList valueList3{"AA3","BB3","CC3"};

    data.addRequest(requestList.at(0), valueList1);
    data.addRequest(requestList.at(1));

    data.setRequestType(requestType);
}

RequestData createRequestData(const TestRequestList& requestList)
{
    RequestData requestData;

    for(int i = 0; i < requestList.count(); ++i)
    {
        requestData.addRequest(requestList.at(i));
    }

    return requestData;
}

