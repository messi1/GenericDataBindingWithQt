#ifndef MOCKDATACLIENTMANAGER_H
#define MOCKDATACLIENTMANAGER_H

#include "IDataClient.h"
#include "IDataClientManager.h"

class MockDataClientManager: public IDataClientManager
{
public:

  MockDataClientManager() = default;
  virtual ~MockDataClientManager() = default;
  void registerClient(const RequestCmd /*requestId*/, IDataClient* /*dataClient*/) final {}
  void deregisterClient(const RequestCmd /*requestId*/, IDataClient* /*dataClient*/) final {}
  void deregisterAllClient(IDataClient* /*dataClient*/) final {}
  void changeRegisteredRequestCmd(IDataClient* /*dataClient*/, const RequestCmd /*oldRequestId*/, const RequestCmd /*newRequestId*/) final {}

  virtual IDataProxy* getDataProxy()  const final {return nullptr;}
  virtual IDataClientManager* clone() const final {return nullptr;}

  void requestSaveData(const RequestCmd /*requestCmd*/, const QString& /*requestValue*/)  final {}
  void requestCommand(const RequestCmd /*commandName*/, const QString& /*inRequesteter*/) final {}
  void requestGetClientData(IDataClient* /*dataClient*/, const RequestCmd /*requestCmd*/, bool /*withRange*/ = true) final;
  void requestGetAllClientData(bool /*withRange*/ = true) final {}

  virtual void newValueReceived( const RequestData &requestData) final { mRequestData = requestData; }
  virtual void newStatusReceived(const RequestData &RequestData) final { mRequestData = RequestData; }

  const RequestData& requestData() const {return mRequestData;}

private:
  RequestData mRequestData;
};

void MockDataClientManager::requestGetClientData(IDataClient* dataClient, const RequestCmd requestCmd, bool withRange)
{
  if( dataClient)
  {
    RequestData requestData(this, nullptr);
    // TODO: Add dataClient to the requestData as return path for special single request, like timer based requests.
    requestData.appendRequestCommand(requestCmd);
    requestData.setRequestType(RequestType::GetValues);
    requestData.setWithRange(withRange);

    dataClient->setValue(requestCmd, "BlaBla");
  }
}
#endif // MOCKDATACLIENTMANAGER_H
