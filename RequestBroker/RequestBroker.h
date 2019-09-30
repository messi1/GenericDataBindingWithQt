#ifndef REQUESTBROKER_H
#define REQUESTBROKER_H

#include "IConnector.h"


class RequestBroker : public IConnector
{
public:
    RequestBroker();
    virtual ~RequestBroker() override = default;
    virtual bool requestData(const RequestData& requestData, RequestData& responseData) final;

};


#endif // REQUESTBROKER_H
