#ifndef TESTDATACLIENT_H
#define TESTDATACLIENT_H

#include <QString>
#include "DataClient.h"

class TestDataClient : public DataClient
{
public:
    TestDataClient() = delete;
    explicit TestDataClient(IDataClientManager& dataClientManager);
    ~TestDataClient() = default;

    void setValue(     const RequestCmd /*requestCmd*/, const QString&     /*requestValue*/, const QString& /*requestRange*/, const int /*status*/) final {}
    void setValue(     const RequestCmd /*requestCmd*/, const QString&     /*requestValue*/) final;
    void setValueList( const RequestCmd /*requestCmd*/, const QStringList& /*requestValueList*/) final {}
    void setStatus(    const RequestCmd /*requestCmd*/, const QString&     /*requestError*/, const int /*status*/) final {}
    void refresh() final {}

private:
    QString mData;
};

TestDataClient::TestDataClient(IDataClientManager& dataClientManager)
  : DataClient(dataClientManager)
{}

void TestDataClient::setValue(const RequestCmd /*requestCmd*/, const QString& requestValue)
{
  mData = requestValue;
}

#endif // TESTDATACLIENT_H
