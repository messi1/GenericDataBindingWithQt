#include "DCCheckBox.h"

DCCheckBox::DCCheckBox(IDataClientManager &dataClientManager, QWidget *parent)
    :QCheckBox(parent),
      DataClient(dataClientManager)
{

}

void DCCheckBox::setValue(const RequestCmd /*requestCmd*/, const QString &/*requestValue*/, const QString &/*requestRange*/, const int /*status*/)
{

}

void DCCheckBox::setValue(const RequestCmd /*requestCmd*/, const QString &/*requestValue*/)
{

}

void DCCheckBox::setValueList(const RequestCmd /*requestCmd*/, const QStringList &/*requestValueList*/)
{

}

void DCCheckBox::setStatus(const RequestCmd /*requestCmd*/, const QString &/*requestError*/, const int /*status*/)
{

}

void DCCheckBox::refresh()
{

}
