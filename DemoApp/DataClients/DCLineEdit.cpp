#include "DCLineEdit.h"

DCLineEdit::DCLineEdit(IDataClientManager &dataClientManager, QWidget *parent)
    :QLineEdit(parent),
     DataClient (dataClientManager)
{

}

void DCLineEdit::setValueList(const Request& /*request*/, const QStringList& /*valueList*/,
                              const QStringList& /*rangeList*/, const QStringList& /*errorList*/)
{

}

void DCLineEdit::refresh()
{

}
