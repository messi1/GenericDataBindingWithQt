#include "DCPushButton.h"

DCPushButton::DCPushButton(IDataClientManager &dataClientManager, QWidget *parent)
    :QPushButton(parent),
      DataClient (dataClientManager)
{

}

void DCPushButton::setValue(const RequestCmd /*requestCmd*/, const QString &/*requestValue*/, const QString &/*requestRange*/, const int /*status*/)
{

}

void DCPushButton::setValue(const RequestCmd /*requestCmd*/, const QString &/*requestValue*/)
{

}

void DCPushButton::setValueList(const RequestCmd /*requestCmd*/, const QStringList &/*requestValueList*/)
{

}

void DCPushButton::setStatus(const RequestCmd /*requestCmd*/, const QString &/*requestError*/, const int /*status*/)
{

}

void DCPushButton::refresh()
{

}
