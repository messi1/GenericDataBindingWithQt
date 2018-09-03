#include "DCTextEdit.h"

DCTextEdit::DCTextEdit(IDataClientManager &dataClientManager, QWidget *parent)
    :QTextEdit(parent),
      DataClient(dataClientManager)
{

}

void DCTextEdit::setValueList(const Request& /*request*/, const QStringList& /*valueList*/,
                              const QStringList& /*rangeList*/, const QStringList& /*errorList*/)
{

}

void DCTextEdit::setStatusList(const Request &/*request*/, const QStringList &/*responseStatusList*/, const QStringList &/*responseErrorList*/)
{

}

void DCTextEdit::refresh()
{

}
