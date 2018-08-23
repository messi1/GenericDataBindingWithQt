#include "RequestCommand.h"

bool operator==(const Request& request1, const Request& request2)
{
    if(request1.requestCmd == request2.requestCmd && request1.withRange == request2.withRange && request1.contexId == request2.contexId)
        return true;
    else
        return false;
}

bool operator<(const Request& request1, const Request& request2)
{
    return  (request1.requestCmd < request2.requestCmd);
}
