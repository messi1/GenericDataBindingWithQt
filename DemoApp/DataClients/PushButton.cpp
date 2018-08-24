#include "PushButton.h"

PushButton::PushButton(IDataClientManager &dataClientManager, QWidget *parent)
    :QPushButton(parent),
      DataClient (dataClientManager)
{

}

void PushButton::setValue(const RequestCmd /*requestCmd*/, const QString &/*requestValue*/, const QString &/*requestRange*/, const int /*status*/)
{

}

void PushButton::setValue(const RequestCmd /*requestCmd*/, const QString &/*requestValue*/)
{

}

void PushButton::setValueList(const RequestCmd /*requestCmd*/, const QStringList &/*requestValueList*/)
{

}

void PushButton::setStatus(const RequestCmd /*requestCmd*/, const QString &/*requestError*/, const int /*status*/)
{

}

void PushButton::refresh()
{

}
