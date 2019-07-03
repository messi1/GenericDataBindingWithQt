#ifndef MOCKDATACLIENTMANAGER_H
#define MOCKDATACLIENTMANAGER_H

#include "IDataClient.h"
#include "IDataClientManager.h"

class MockDataClientManager: public IDataClientManager
{
public:

  MockDataClientManager() = default;
  virtual ~MockDataClientManager() = default;
  void registerClient(const Request& /*request*/, IDataClient* /*dataClient*/) final {}
  void deregisterClient(const Request& /*request*/, IDataClient* /*dataClient*/) final {}
  void deregisterAllClient(IDataClient* /*dataClient*/) final {}
  void changeRegisteredRequest(IDataClient* /*dataClient*/, const Request& /*oldRequest*/, const Request& /*newRequest*/) final {}

  virtual IDataProxy* dataProxy()  const final {return nullptr;}
  virtual IDataClientManager* clone() const final {return nullptr;}

  void requestData(const RequestData& /*requestData*/) final {}
  void requestSaveData(const Request& /*saveRequest*/,   const QStringList& /*valueList*/) final {}
  void requestCommand(const Request& /*commandRequest*/, const QStringList& /*valueList*/) final {}
  void requestGetClientData(IDataClient* /*dataClient*/, const Request& /*request*/) final;
  void requestGetAllClientData() final {}

  virtual void newValueReceived( const ResponseData &responseData) final { mRequestData = responseData; }

  const ResponseData& requestData() const {return mRequestData;}

private:
  ResponseData mRequestData;
};

void MockDataClientManager::requestGetClientData(IDataClient* dataClient, const Request& request)
{
  if( dataClient)
  {
    RequestData requestData(this, nullptr);
    // TODO: Add dataClient to the requestData as return path for special single request, like timer based requests.
    requestData.addRequest(request);
    requestData.setRequestType(RequestType::GetValues);

    dataClient->setValueList(request, {"BlaBla"}, QStringList());
  }
}
#endif // MOCKDATACLIENTMANAGER_H
