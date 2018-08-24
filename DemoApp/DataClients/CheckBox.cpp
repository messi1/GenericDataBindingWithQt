#include "CheckBox.h"

CheckBox::CheckBox(IDataClientManager &dataClientManager, QWidget *parent)
    :QCheckBox(parent),
      DataClient(dataClientManager)
{

}

void CheckBox::setValue(const RequestCmd /*requestCmd*/, const QString &/*requestValue*/, const QString &/*requestRange*/, const int /*status*/)
{

}

void CheckBox::setValue(const RequestCmd /*requestCmd*/, const QString &/*requestValue*/)
{

}

void CheckBox::setValueList(const RequestCmd /*requestCmd*/, const QStringList &/*requestValueList*/)
{

}

void CheckBox::setStatus(const RequestCmd /*requestCmd*/, const QString &/*requestError*/, const int /*status*/)
{

}

void CheckBox::refresh()
{

}
