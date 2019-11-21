#ifndef MOCKDATACLIENTMANAGER_H
#define MOCKDATACLIENTMANAGER_H

#include "DataBinding/IDataClient.h"
#include "DataBinding/IDataClientManager.h"

class MockDataClientManager: public IDataClientManager, QEnableSharedFromThis<MockDataClientManager>
{
public:
  MockDataClientManager() = default;
  ~MockDataClientManager() override = default;
  void registerClient(const Request& /*request*/, IDataClient* /*dataClient*/) final {}
  void deregisterClient(const Request& /*request*/, IDataClient* /*dataClient*/) final {}
  void deregisterAllClient(IDataClient* /*dataClient*/) final {}
  void changeRegisteredRequest(IDataClient* /*dataClient*/, const Request& /*oldRequest*/, const Request& /*newRequest*/) final {}

  [[nodiscard]] DataProxyWeakPtr    dataProxy() const final { return {}; }
  [[nodiscard]] IDataClientManager *clone() const final { return nullptr; }

  void requestData(const RequestData& /*requestData*/) final {}
  void requestSaveData(const Request& /*saveRequest*/,   const QStringList& /*valueList*/) final {}
  void requestCommand(const Request& /*commandRequest*/, const QStringList& /*valueList*/) final {}
  void requestGetClientData(IDataClient* /*dataClient*/, const Request& /*request*/) final;
  void requestGetAllClientData() final {}

  void newValueReceived(const ResponseData &responseData) final { mRequestData = responseData; }

  [[nodiscard]] const ResponseData &requestData() const { return mRequestData; }

  private:
  ResponseData mRequestData;
};

inline void MockDataClientManager::requestGetClientData(IDataClient *dataClient, const Request &request)
{
  if( dataClient)
  {
    RequestData requestData(sharedFromThis().toWeakRef(), dataProxy());
    // TODO: Add dataClient to the requestData as return path for special single request, like timer based requests.
    requestData.addRequest(request);
    requestData.setRequestType(RequestType::GetValues);

    dataClient->setValueList(request, {"BlaBla"}, QStringList());
  }
}
#endif // MOCKDATACLIENTMANAGER_H
