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
    QSharedPointer<MockDataProxy> dataProxyPtr(new MockDataProxy);
    DataClientManager clientManager(dataProxyPtr.toWeakRef());
    TestDataClient testClient(clientManager);

    clientManager.registerClient({RequestCmd::DateTime}, nullptr);

    EXPECT_EQ( clientManager.numberOfRegisterdRequests(), 0);
}

TEST(DataClientManager, deregisterNullPtrClient)
{
    QSharedPointer<MockDataProxy> dataProxyPtr(new MockDataProxy);
    DataClientManager clientManager(dataProxyPtr.toWeakRef());
    TestDataClient testClient(clientManager);

    clientManager.registerClient({RequestCmd::DateTime}, &testClient);
    EXPECT_EQ( clientManager.numberOfRegisterdRequests(), 1);

    clientManager.deregisterClient({RequestCmd::DateTime}, nullptr);

    EXPECT_EQ( clientManager.numberOfRegisterdRequests(), 1);
}

TEST(DataClientManager, registerClient)
{
    QSharedPointer<MockDataProxy> dataProxyPtr(new MockDataProxy);
    DataClientManager clientManager(dataProxyPtr.toWeakRef());
    TestDataClient testClient(clientManager);

    EXPECT_EQ( clientManager.numberOfRegisterdRequests(), 0);
    clientManager.registerClient({RequestCmd::BatteryState}, &testClient);
    EXPECT_EQ( clientManager.numberOfRegisterdRequests(), 1);
    clientManager.registerClient({RequestCmd::EthState}, &testClient);
    EXPECT_EQ( clientManager.numberOfRegisterdRequests(), 2);
}

TEST(DataClientManager, deregisterClient)
{
    QSharedPointer<MockDataProxy> dataProxyPtr(new MockDataProxy);
    DataClientManager clientManager(dataProxyPtr.toWeakRef());
    TestDataClient testClient(clientManager);

    EXPECT_EQ( clientManager.numberOfRegisterdRequests(), 0);
    clientManager.registerClient({RequestCmd::BatteryState}, &testClient);
    EXPECT_EQ( clientManager.numberOfRegisterdRequests(), 1);
    clientManager.deregisterClient({RequestCmd::BatteryState}, &testClient);
    EXPECT_EQ( clientManager.numberOfRegisterdRequests(), 0);
}

TEST(DataClientManager, doubleClientRegistration)
{
    QSharedPointer<MockDataProxy> dataProxyPtr(new MockDataProxy);
    DataClientManager clientManager(dataProxyPtr.toWeakRef());
    TestDataClient testClient(clientManager);

    EXPECT_EQ( clientManager.numberOfRegisterdRequests(), 0);
    clientManager.registerClient({RequestCmd::DateTime}, &testClient);
    clientManager.registerClient({RequestCmd::DateTime}, &testClient);
    clientManager.registerClient({RequestCmd::DateTime}, &testClient);
    EXPECT_EQ( clientManager.numberOfRegisterdRequests(), 1);
}

TEST(DataClientManager, deregisterAllClientFromRequests)
{
    QSharedPointer<MockDataProxy> dataProxyPtr(new MockDataProxy);
    DataClientManager clientManager(dataProxyPtr.toWeakRef());
    TestDataClient testClient(clientManager);

    EXPECT_EQ( clientManager.numberOfRegisterdRequests(), 0);
    clientManager.registerClient({RequestCmd::DateTime},     &testClient);
    clientManager.registerClient({RequestCmd::EthState},     &testClient);
    clientManager.registerClient({RequestCmd::BatteryState}, &testClient);
    EXPECT_EQ( clientManager.numberOfRegisterdRequests(), 3);
}

TEST(DataClientManager, changeRegisteredRequestCmd)
{
    QSharedPointer<MockDataProxy> dataProxyPtr(new MockDataProxy);
    DataClientManager clientManager(dataProxyPtr.toWeakRef());
    TestDataClient testClient(clientManager);

    EXPECT_EQ( clientManager.numberOfRegisterdRequests(), 0);
    clientManager.registerClient({RequestCmd::DateTime},    &testClient);
    clientManager.registerClient({RequestCmd::EthState},     &testClient);
    clientManager.registerClient({RequestCmd::BatteryState}, &testClient);
    EXPECT_EQ( clientManager.numberOfRegisterdRequests(), 3);
    clientManager.changeRegisteredRequest(&testClient, {RequestCmd::BatteryState}, {RequestCmd::WlanState});
    EXPECT_EQ( clientManager.numberOfRegisterdRequests(), 3);

    RequestList requestList = clientManager.allClientRequests(&testClient);

    EXPECT_TRUE(requestList.contains({RequestCmd::DateTime}));
    EXPECT_TRUE(requestList.contains({RequestCmd::EthState}));
    EXPECT_TRUE(requestList.contains({RequestCmd::WlanState}));
}

#endif // TST_DATACLIENTMANAGER_H
