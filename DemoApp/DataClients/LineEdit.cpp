#include "LineEdit.h"

LineEdit::LineEdit(IDataClientManager &dataClientManager, QWidget *parent)
    :QLineEdit(parent),
     DataClient (dataClientManager)
{

}

void LineEdit::setValue(const RequestCmd /*requestCmd*/, const QString &/*requestValue*/, const QString &/*requestRange*/, const int /*status*/)
{

}

void LineEdit::setValue(const RequestCmd /*requestCmd*/, const QString &/*requestValue*/)
{

}

void LineEdit::setValueList(const RequestCmd /*requestCmd*/, const QStringList &/*requestValueList*/)
{

}

void LineEdit::setStatus(const RequestCmd /*requestCmd*/, const QString &/*requestError*/, const int /*status*/)
{

}

void LineEdit::refresh()
{

}
