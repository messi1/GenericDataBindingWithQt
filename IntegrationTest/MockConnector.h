#ifndef MOCKCONNECTOR_H
#define MOCKCONNECTOR_H

#include "RequestBroker/IConnector.h"
#include "DataProvider/DataProviderTest/TestValues.h"

class RequestData;

class MockConnector: public IConnector
{
  public:
    bool requestData(const RequestData& requestData, RequestData& responseData) override
    {
        TestValues testData;

        responseData.clearAllData();
        responseData = testData.responseData1;
        responseData.setDataProxy(requestData.dataProxy());
        responseData.setDataClientManager(requestData.dataClientManager());

        return true;
    }
};

#endif // MOCKCONNECTOR_H
