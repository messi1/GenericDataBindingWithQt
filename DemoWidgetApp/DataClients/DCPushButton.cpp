#include "DCPushButton.h"

DCPushButton::DCPushButton(IDataClientManager &dataClientManager, QWidget *parent)
    :QPushButton(parent),
      DataClient (dataClientManager)
{

}

void DCPushButton::setValueList(const Request& /*request*/, const QStringList& /*valueList*/, const QStringList& /*rangeList*/)
{

}

void DCPushButton::setAccessRights(const QString &/*accessRights*/)
{

}

void DCPushButton::setErrorList(const Request &/*request*/, const QStringList &/*responseErrorList*/)
{

}

void DCPushButton::refresh()
{

}
