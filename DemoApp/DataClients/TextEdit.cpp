#include "TextEdit.h"

TextEdit::TextEdit(IDataClientManager &dataClientManager, QWidget *parent)
    :QTextEdit(parent),
      DataClient(dataClientManager)
{

}

void TextEdit::setValue(const RequestCmd /*requestCmd*/, const QString &/*requestValue*/, const QString &/*requestRange*/, const int /*status*/)
{

}

void TextEdit::setValue(const RequestCmd /*requestCmd*/, const QString &/*requestValue*/)
{

}

void TextEdit::setValueList(const RequestCmd /*requestCmd*/, const QStringList &/*requestValueList*/)
{

}

void TextEdit::setStatus(const RequestCmd /*requestCmd*/, const QString &/*requestError*/, const int /*status*/)
{

}

void TextEdit::refresh()
{

}
