#include "DCTextEdit.h"

DCTextEdit::DCTextEdit(IDataClientManager &dataClientManager, QWidget *parent)
    :QTextEdit(parent),
      DataClient(dataClientManager)
{

}

void DCTextEdit::setValue(const RequestCmd /*requestCmd*/, const QString &/*requestValue*/, const QString &/*requestRange*/, const int /*status*/)
{

}

void DCTextEdit::setValue(const RequestCmd /*requestCmd*/, const QString &/*requestValue*/)
{

}

void DCTextEdit::setValueList(const RequestCmd /*requestCmd*/, const QStringList &/*requestValueList*/)
{

}

void DCTextEdit::setStatus(const RequestCmd /*requestCmd*/, const QString &/*requestError*/, const int /*status*/)
{

}

void DCTextEdit::refresh()
{

}
