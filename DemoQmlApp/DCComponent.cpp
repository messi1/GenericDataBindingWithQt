#include "DCComponent.h"

DCComponent::DCComponent(IDataProxy &dataProxy, QObject *parent)
    :  QObject(parent), DataClientManager(dataProxy)
{

}
