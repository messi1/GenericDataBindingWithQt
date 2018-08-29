#include "DCLabel.h"

DCLabel::DCLabel(IDataClientManager &dataClientManager, QWidget *parent)
    :QLabel(parent),
      DataClient(dataClientManager)
{

}

void DCLabel::setValue(const RequestCmd /*requestCmd*/, const QString &/*requestValue*/, const QString &/*requestRange*/, const int /*status*/)
{

}

void DCLabel::setValue(const RequestCmd /*requestCmd*/, const QString &/*requestValue*/)
{

}

void DCLabel::setValueList(const RequestCmd /*requestCmd*/, const QStringList &/*requestValueList*/)
{

}

void DCLabel::setStatus(const RequestCmd /*requestCmd*/, const QString &/*requestError*/, const int /*status*/)
{

}

void DCLabel::refresh()
{

}
