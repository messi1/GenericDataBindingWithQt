#include "TestValues.h"

RequestData fillRequestData(const TestRequestList& requestList)
{
    RequestData requestData;

    for(int i = 0; i < requestList.count(); ++i)
    {
        requestData.appendRequest(requestList.at(i));
    }

    return requestData;
}

RequestData fillRequestData(const TestRequestList& requestList, const TestStringListList& valueListList)
{
    RequestData requestData;

    for(int i = 0; i < requestList.count(); ++i)
    {
        QStringList valueList;

        if(valueListList.count() > i)
            valueList = valueListList.at(i);

        requestData.appendRequest(requestList.at(i), valueList);
    }

    return requestData;
}

RequestData fillRequestData(const TestRequestList& requestList, const TestStringListList& valueListList, const TestStringListList& rangeListList)
{
    RequestData requestData;

    for(int i = 0; i < requestList.count(); ++i)
    {
        QStringList valueList;
        QStringList rangeList;

        if(valueListList.count() > i)
            valueList = valueListList.at(i);

        if(rangeListList.count() > i)
            rangeList = rangeListList.at(i);

        requestData.appendRequest(requestList.at(i), valueList, rangeList);
    }

    return requestData;
}

RequestData fillRequestData(const TestRequestList& requestList, const TestStringListList& valueListList, const TestStringListList& rangeListList, const TestStringListList& errorListList)
{
    RequestData requestData;

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

        requestData.appendRequest(requestList.at(i), valueList, rangeList, errorList);
    }

    return requestData;
}
