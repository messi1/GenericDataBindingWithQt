#include "DCPushButton.h"

DCPushButton::DCPushButton(IDataClientManager &dataClientManager, QWidget *parent)
    :QPushButton(parent),
      DataClient (dataClientManager)
{

}

void DCPushButton::setValueList(const Request& /*request*/, const QStringList& /*valueList*/,
                                const QStringList& /*rangeList*/, const QStringList& /*errorList*/)
{

}

void DCPushButton::setStatusList(const Request &/*request*/, const QStringList &/*responseStatusList*/, const QStringList &/*responseErrorList*/)
{

}

void DCPushButton::refresh()
{

}
