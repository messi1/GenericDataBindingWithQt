#include "BaseFrame.h"
#include "DataProvider/IDataProxy.h"
#include "RequestData/RequestCommand.h"

BaseFrame::BaseFrame(IDataProxy &dataProxy, QWidget *parent)
    :QFrame(parent),
      DataClientManager(&dataProxy)
{
    RequestData requestData(this, DataClientManager::dataProxy());
    requestData.setRequestType(RequestType::GetValues);
    requestData.addRequest({RequestCmd::Language, true});

    DataClientManager::dataProxy()->requestData(requestData);
}

void BaseFrame::showEvent(QShowEvent *event)
{
    DataClientManager::requestGetAllClientData();
    QFrame::showEvent(event);
}
