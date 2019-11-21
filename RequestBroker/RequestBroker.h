#ifndef REQUESTBROKER_H
#define REQUESTBROKER_H

#include "IConnector.h"


class RequestBroker : public IConnector
{
public:
    RequestBroker()=default;
    ~RequestBroker() override = default;
    bool requestData(const RequestData& requestData, ResponseData& responseData) override;

};


#endif // REQUESTBROKER_H
