#ifndef TST_DATACLIENTMANAGER_H
#define TST_DATACLIENTMANAGER_H

#include "RequestData/RequestCommand.h"

#include "DataClientManager.h"
#include "MockDataProxy.h"
#include "TestDataClient.h"

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

TEST(DataClientManager, registerNullPtrClient)
{
    MockDataProxy dataProxy;
    DataClientManager clientManager(dataProxy);
    TestDataClient testClient(clientManager);

    clientManager.registerClient({RequestCmd::DateTime}, nullptr);

    EXPECT_EQ( clientManager.numberOfRegisterdRequests(), 0);
}

TEST(DataClientManager, deregisterNullPtrClient)
{
    MockDataProxy dataProxy;
    DataClientManager clientManager(dataProxy);
    TestDataClient testClient(clientManager);

    clientManager.registerClient({RequestCmd::DateTime}, &testClient);
    EXPECT_EQ( clientManager.numberOfRegisterdRequests(), 1);

    clientManager.deregisterClient({RequestCmd::DateTime}, nullptr);

    EXPECT_EQ( clientManager.numberOfRegisterdRequests(), 1);
}

TEST(DataClientManager, registerClient)
{
    MockDataProxy dataProxy;
    DataClientManager clientManager(dataProxy);
    TestDataClient testClient(clientManager);

    EXPECT_EQ( clientManager.numberOfRegisterdRequests(), 0);
    clientManager.registerClient({RequestCmd::BatteryState}, &testClient);
    EXPECT_EQ( clientManager.numberOfRegisterdRequests(), 1);
    clientManager.registerClient({RequestCmd::EthState}, &testClient);
    EXPECT_EQ( clientManager.numberOfRegisterdRequests(), 2);
}

TEST(DataClientManager, deregisterClient)
{
    MockDataProxy dataProxy;
    DataClientManager clientManager(dataProxy);
    TestDataClient testClient(clientManager);

    EXPECT_EQ( clientManager.numberOfRegisterdRequests(), 0);
    clientManager.registerClient({RequestCmd::BatteryState}, &testClient);
    EXPECT_EQ( clientManager.numberOfRegisterdRequests(), 1);
    clientManager.deregisterClient({RequestCmd::BatteryState}, &testClient);
    EXPECT_EQ( clientManager.numberOfRegisterdRequests(), 0);
}

TEST(DataClientManager, doubleClientRegistration)
{
    MockDataProxy dataProxy;
    DataClientManager clientManager(dataProxy);
    TestDataClient testClient(clientManager);

    EXPECT_EQ( clientManager.numberOfRegisterdRequests(), 0);
    clientManager.registerClient({RequestCmd::DateTime}, &testClient);
    clientManager.registerClient({RequestCmd::DateTime}, &testClient);
    clientManager.registerClient({RequestCmd::DateTime}, &testClient);
    EXPECT_EQ( clientManager.numberOfRegisterdRequests(), 1);
}

TEST(DataClientManager, deregisterAllClientFromRequests)
{
    MockDataProxy dataProxy;
    DataClientManager clientManager(dataProxy);
    TestDataClient testClient(clientManager);

    EXPECT_EQ( clientManager.numberOfRegisterdRequests(), 0);
    clientManager.registerClient({RequestCmd::DateTime},     &testClient);
    clientManager.registerClient({RequestCmd::EthState},     &testClient);
    clientManager.registerClient({RequestCmd::BatteryState}, &testClient);
    EXPECT_EQ( clientManager.numberOfRegisterdRequests(), 3);
}

TEST(DataClientManager, changeRegisteredRequestCmd)
{
    MockDataProxy dataProxy;
    DataClientManager clientManager(dataProxy);
    TestDataClient testClient(clientManager);

    EXPECT_EQ( clientManager.numberOfRegisterdRequests(), 0);
    clientManager.registerClient({RequestCmd::DateTime},    &testClient);
    clientManager.registerClient({RequestCmd::EthState},     &testClient);
    clientManager.registerClient({RequestCmd::BatteryState}, &testClient);
    EXPECT_EQ( clientManager.numberOfRegisterdRequests(), 3);
    clientManager.changeRegisteredRequest(&testClient, {RequestCmd::BatteryState}, {RequestCmd::WlanState});
    EXPECT_EQ( clientManager.numberOfRegisterdRequests(), 3);

    RequestVector cmdVector = clientManager.allRequestsOfAClient(&testClient);

    EXPECT_TRUE(cmdVector.contains({RequestCmd::DateTime}));
    EXPECT_TRUE(cmdVector.contains({RequestCmd::EthState}));
    EXPECT_TRUE(cmdVector.contains({RequestCmd::WlanState}));
}

#endif // TST_DATACLIENTMANAGER_H
