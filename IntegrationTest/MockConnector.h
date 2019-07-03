#ifndef MOCKCONNECTOR_H
#define MOCKCONNECTOR_H

#include "RequestBroker/IConnector.h"
#include "RequestResponseData/RequestResponseDataTest/TestRequestValues.h"
#include "RequestResponseData/RequestResponseDataTest/TestResponseValues.h"

class RequestData;

class MockConnector: public IConnector
{
  public:
    bool requestData(const RequestData& requestData, ResponseData& responseData) override
    {
        responseData.clearAllData();
        responseData = TestResponseValues().responseData1;
        responseData.setDataProxy(requestData.dataProxy());
        responseData.setDataClientManager(requestData.dataClientManager());

        return true;
    }
};

#endif // MOCKCONNECTOR_H
