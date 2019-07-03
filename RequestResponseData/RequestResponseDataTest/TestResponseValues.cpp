#include "TestResponseValues.h"

void fillResponseData(ResponseData& data)
{
  const RequestType requestType = RequestType::GetValues;
  QList<Request> requestList{{RequestCmd::BatteryState, true, 3}, {RequestCmd::EthState, false, 1}, {RequestCmd::WlanState, true, 2}};

  const QStringList valueList1{"AA1","BB1","CC1"};
  const QStringList valueList2{"AA2","BB2","CC2"};
  const QStringList valueList3{"AA3","BB3","CC3"};


  const QStringList rangeList1{"111","222","333"};
  const QStringList rangeList2{"444","555","666"};
  const QStringList rangeList3{"777","888","999"};

  const QStringList errorList1{"E1AA","E2BB","E3CC"};
  const QStringList errorList2{"E4AA","E5BB","E6CC"};
  const QStringList errorList3{"E7AA","E8BB","E9CC"};

  data.addResponse(requestList.at(0), valueList1, rangeList1, errorList1);
  data.addResponse(requestList.at(1), valueList1, rangeList2, errorList2);
  data.addResponse(requestList.at(2), valueList1, rangeList3, errorList3);

  data.setRequestType(requestType);
}

ResponseData createResponseData(const TestRequestList& requestList)
{
    ResponseData responseData;

    for(int i = 0; i < requestList.count(); ++i)
    {
        responseData.addResponse(requestList.at(i));
    }

    return responseData;
}

ResponseData createResponseData(const TestRequestList& requestList, const TestStringList& valueListList)
{
    ResponseData responseData;

    for(int i = 0; i < requestList.count(); ++i)
    {
        QStringList valueList;

        if(valueListList.count() > i)
            valueList = valueListList.at(i);

        responseData.addResponse(requestList.at(i), valueList);
    }

    return responseData;
}

ResponseData createResponseData(const TestRequestList& requestList, const TestStringList& valueListList, const TestStringList& rangeListList)
{
    ResponseData responseData;

    for(int i = 0; i < requestList.count(); ++i)
    {
        QStringList valueList;
        QStringList rangeList;

        if(valueListList.count() > i)
            valueList = valueListList.at(i);

        if(rangeListList.count() > i)
            rangeList = rangeListList.at(i);

        responseData.addResponse(requestList.at(i), valueList, rangeList);
    }

    return responseData;
}

ResponseData createResponseData(const TestRequestList& requestList, const TestStringList& valueListList, const TestStringList& rangeListList, const TestStringList& errorListList)
{
    ResponseData responseData;

    for(int i = 0; i < requestList.count(); ++i)
    {
        QStringList valueList;
        QStringList rangeList;
        QStringList errorList;

        if(valueListList.count() > i)
            valueList = valueListList.at(i);

        if(rangeListList.count() > i)
            rangeList = rangeListList.at(i);

        if(errorListList.count() > i)
            errorList = errorListList.at(i);

        responseData.addResponse(requestList.at(i), valueList, rangeList, errorList);
    }

    return responseData;
}
