#include "DCComponent.h"

DCComponent::DCComponent(QSharedPointer<IDataProxy> &dataProxyPtr, QObject *parent)
    :  QObject(parent), DataClientManager(dataProxyPtr)
{

}
