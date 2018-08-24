#include "ComboBox.h"

ComboBox::ComboBox(IDataClientManager &dataClientManager, QWidget *parent)
    :QComboBox(parent),
      DataClient (dataClientManager)
{

}

void ComboBox::setValue(const RequestCmd /*requestCmd*/, const QString &/*requestValue*/, const QString &/*requestRange*/, const int /*status*/)
{

}

void ComboBox::setValue(const RequestCmd /*requestCmd*/, const QString &/*requestValue*/)
{

}

void ComboBox::setValueList(const RequestCmd /*requestCmd*/, const QStringList &/*requestValueList*/)
{

}

void ComboBox::setStatus(const RequestCmd /*requestCmd*/, const QString &/*requestError*/, const int /*status*/)
{

}

void ComboBox::refresh()
{

}
