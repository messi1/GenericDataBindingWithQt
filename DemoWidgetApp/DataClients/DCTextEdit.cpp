#include "DCTextEdit.h"

DCTextEdit::DCTextEdit(IDataClientManager &dataClientManager, QWidget *parent)
    :QTextEdit(parent),
      DataClient(dataClientManager)
{

}

void DCTextEdit::setAccessRights(const QString &/*accessRights*/)
{

}

void DCTextEdit::setErrorList(const Request &/*request*/, const QStringList &/*responseErrorList*/)
{

}

void DCTextEdit::setValueList(const Request& /*request*/, const QStringList& /*valueList*/, const QStringList& /*rangeList*/)
{

}

void DCTextEdit::refresh()
{

}
