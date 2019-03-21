#include <QDebug>
#include "DCComponent.h"

DCComponent::DCComponent()
{
    qDebug() << "Constructor DCComponent1";
}

DCComponent::DCComponent(IDataProxy &dataProxy, QObject *parent)
    :  QObject(parent), DataClientManager(&dataProxy)
{
    qDebug() << "Constructor DCComponent2";
}
