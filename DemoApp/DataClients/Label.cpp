#include "Label.h"

Label::Label(IDataClientManager &dataClientManager, QWidget *parent)
    :QLabel(parent),
      DataClient(dataClientManager)
{

}

void Label::setValue(const RequestCmd /*requestCmd*/, const QString &/*requestValue*/, const QString &/*requestRange*/, const int /*status*/)
{

}

void Label::setValue(const RequestCmd /*requestCmd*/, const QString &/*requestValue*/)
{

}

void Label::setValueList(const RequestCmd /*requestCmd*/, const QStringList &/*requestValueList*/)
{

}

void Label::setStatus(const RequestCmd /*requestCmd*/, const QString &/*requestError*/, const int /*status*/)
{

}

void Label::refresh()
{

}
