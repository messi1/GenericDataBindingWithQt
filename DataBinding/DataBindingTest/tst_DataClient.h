#ifndef TST_DATACLIENT_H
#define TST_DATACLIENT_H

#include "TestDataClient.h"
#include "MockDataClientManager.h"

#include "RequestData/RequestCommand.h"

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

TEST(DataClient, Test11)
{
  MockDataClientManager dataClientManager;
  TestDataClient testClient(dataClientManager);

  testClient.requestGetData(RequestCmd::BatteryState);

}

#endif // TST_DATACLIENT_H
