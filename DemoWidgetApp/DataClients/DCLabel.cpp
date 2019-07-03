#include "DCLabel.h"

DCLabel::DCLabel(IDataClientManager &dataClientManager, QWidget *parent)
    :QLabel(parent),
      DataClient(dataClientManager)
{

}

void DCLabel::setAccessRights(const QString &/*accessRights*/)
{

}

void DCLabel::setValueList(const Request& /*request*/, const QStringList& /*valueList*/,
                           const QStringList& /*rangeList*/)
{

}

void DCLabel::setErrorList(const Request &/*request*/, const QStringList &/*responseErrorList*/)
{

}

void DCLabel::refresh()
{

}
