#ifndef MOCKDATACLIENTMANAGER_H
#define MOCKDATACLIENTMANAGER_H

#include "IDataClient.h"
#include "IDataClientManager.h"

class MockDataClientManager: public IDataClientManager
{
public:

  MockDataClientManager() = default;
  virtual ~MockDataClientManager() = default;
  void registerClient(const Request /*request*/, IDataClient* /*dataClient*/) final {}
  void deregisterClient(const Request /*request*/, IDataClient* /*dataClient*/) final {}
  void deregisterAllClient(IDataClient* /*dataClient*/) final {}
  void changeRegisteredRequest(IDataClient* /*dataClient*/, const Request /*oldRequest*/, const Request /*newRequest*/) final {}

  virtual IDataProxy* dataProxy()  const final {return nullptr;}
  virtual IDataClientManager* clone() const final {return nullptr;}

  void requestSaveData(const Request /*request*/, const QString& /*requestValue*/)  final {}
  void requestCommand(const Request /*commandName*/, const QString& /*inRequesteter*/) final {}
  void requestGetClientData(IDataClient* /*dataClient*/, const Request& /*request*/) final;
  void requestGetAllClientData() final {}

  virtual void newValueReceived( const RequestData &requestData) final { mRequestData = requestData; }
  virtual void newStatusReceived(const RequestData &RequestData) final { mRequestData = RequestData; }

  const RequestData& requestData() const {return mRequestData;}

private:
  RequestData mRequestData;
};

void MockDataClientManager::requestGetClientData(IDataClient* dataClient, const Request& request)
{
  if( dataClient)
  {
    RequestData requestData(this, nullptr);
    // TODO: Add dataClient to the requestData as return path for special single request, like timer based requests.
    requestData.appendRequest(request);
    requestData.setRequestType(RequestType::GetValues);

    dataClient->setValue(request.requestCmd, "BlaBla");
  }
}
#endif // MOCKDATACLIENTMANAGER_H
