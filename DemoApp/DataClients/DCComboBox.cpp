#include "DCComboBox.h"

DCComboBox::DCComboBox(IDataClientManager &dataClientManager, QWidget *parent)
    :QComboBox(parent),
      DataClient (dataClientManager)
{

}

void DCComboBox::setValue(const RequestCmd /*requestCmd*/, const QString &/*requestValue*/, const QString &/*requestRange*/, const int /*status*/)
{

}

void DCComboBox::setValue(const RequestCmd /*requestCmd*/, const QString &/*requestValue*/)
{

}

void DCComboBox::setValueList(const RequestCmd /*requestCmd*/, const QStringList &/*requestValueList*/)
{

}

void DCComboBox::setStatus(const RequestCmd /*requestCmd*/, const QString &/*requestError*/, const int /*status*/)
{

}

void DCComboBox::refresh()
{

}
