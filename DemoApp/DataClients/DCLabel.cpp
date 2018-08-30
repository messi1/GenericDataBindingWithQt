#include "DCLabel.h"

DCLabel::DCLabel(IDataClientManager &dataClientManager, QWidget *parent)
    :QLabel(parent),
      DataClient(dataClientManager)
{

}

void DCLabel::setValueList(const Request& /*request*/, const QStringList& /*valueList*/,
                           const QStringList& /*rangeList*/, const QStringList& /*errorList*/)
{

}

void DCLabel::refresh()
{

}
