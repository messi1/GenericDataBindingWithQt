#include "BaseFrame.h"
#include "DataProvider/IDataProxy.h"
#include "RequestResponseData/RequestCommand.h"

BaseFrame::BaseFrame(const QSharedPointer<IDataProxy> &dataProxyPtr, QWidget *parent)
    :QFrame(parent),
      DataClientManager(dataProxyPtr)
{
    RequestData requestData(this->sharedFromThis(), DataClientManager::dataProxy());
    requestData.setRequestType(RequestType::GetValues);
    requestData.addRequest({RequestCmd::Language, true});

    DataClientManager::dataProxy().toStrongRef()->requestData(requestData);
}

void BaseFrame::showEvent(QShowEvent *event)
{
    DataClientManager::requestGetAllClientData();
    QFrame::showEvent(event);
}
