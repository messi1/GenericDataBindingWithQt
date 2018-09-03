#include "RequestCommand.h"

bool operator==(const Request& request1, const Request& request2)
{
    if(request1.requestCmd == request2.requestCmd && request1.withRange == request2.withRange && request1.contextId == request2.contextId)
        return true;
    else
        return false;
}

bool operator<(const Request& request1, const Request& request2)
{
    return  (request1.requestCmd < request2.requestCmd);
}
