#ifndef TESTDATACLIENT_H
#define TESTDATACLIENT_H

#include <QString>
#include "DataClient.h"

class TestDataClient : public DataClient
{
public:
    TestDataClient() = delete;
    explicit TestDataClient(IDataClientManager& dataClientManager);
    ~TestDataClient() override = default;

    void setValueList( const Request& /*requestCmd*/, const QStringList& /*valueList*/,
                       const QStringList& /*rangeList*/, const QStringList& /*errorList*/) final;
    void setStatusList( const Request& /*requestCmd*/, const QStringList& /*rangeList*/, const QStringList& /*errorList*/) final {}
    void setAccessRights(const QString& /*accessRights*/) override
    {

    }
    void refresh() final {}

private:
    QString mData;
};

TestDataClient::TestDataClient(IDataClientManager& dataClientManager)
  : DataClient(dataClientManager)
{}

void TestDataClient::setValueList(const Request& /*requestCmd*/, const QStringList& valueList, const QStringList& /*rangeList*/, const QStringList& /*errorList*/)
{
  if(valueList.count() > 0)
    mData = valueList.at(0);
}

#endif // TESTDATACLIENT_H
