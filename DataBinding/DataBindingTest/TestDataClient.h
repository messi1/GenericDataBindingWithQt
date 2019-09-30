#ifndef TESTDATACLIENT_H
#define TESTDATACLIENT_H

#include <QString>
#include "DataBinding/DataClient.h"

class TestDataClient : public DataClient
{
public:
    TestDataClient() = delete;
    explicit TestDataClient(IDataClientManager& dataClientManager);
    ~TestDataClient() override = default;

    void setValueList( const Request& /*requestCmd*/, const QStringList& /*valueList*/,
                       const QStringList& /*rangeList*/) final;
    void setAccessRights(const QString& /*accessRights*/) override {}
    void setErrorList(const Request& /*request*/, const QStringList& /*responseErrorList*/) override {}
    void refresh() final {}

private:
    QString mData;
};

TestDataClient::TestDataClient(IDataClientManager& dataClientManager)
  : DataClient(dataClientManager)
{}

void TestDataClient::setValueList(const Request& /*requestCmd*/, const QStringList& valueList, const QStringList& /*rangeList*/)
{
  if(valueList.count() > 0)
    mData = valueList.at(0);
}

#endif // TESTDATACLIENT_H
