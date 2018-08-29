#include "DCLineEdit.h"

DCLineEdit::DCLineEdit(IDataClientManager &dataClientManager, QWidget *parent)
    :QLineEdit(parent),
     DataClient (dataClientManager)
{

}

void DCLineEdit::setValue(const RequestCmd /*requestCmd*/, const QString &/*requestValue*/, const QString &/*requestRange*/, const int /*status*/)
{

}

void DCLineEdit::setValue(const RequestCmd /*requestCmd*/, const QString &/*requestValue*/)
{

}

void DCLineEdit::setValueList(const RequestCmd /*requestCmd*/, const QStringList &/*requestValueList*/)
{

}

void DCLineEdit::setStatus(const RequestCmd /*requestCmd*/, const QString &/*requestError*/, const int /*status*/)
{

}

void DCLineEdit::refresh()
{

}
