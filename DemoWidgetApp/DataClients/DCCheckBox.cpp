#include "DCCheckBox.h"

DCCheckBox::DCCheckBox(IDataClientManager &dataClientManager, QWidget *parent)
    :QCheckBox(parent),
      DataClient(dataClientManager)
{

}

void DCCheckBox::setValueList(const Request& /*request*/, const QStringList& /*valueList*/, const QStringList& /*rangeList*/)
{

}

void DCCheckBox::setAccessRights(const QString &/*accessRights*/)
{

}

void DCCheckBox::setErrorList(const Request &/*request*/, const QStringList &/*responseErrorList*/)
{

}



void DCCheckBox::refresh()
{

}
