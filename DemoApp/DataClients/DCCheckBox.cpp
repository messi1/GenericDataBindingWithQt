#include "DCCheckBox.h"

DCCheckBox::DCCheckBox(IDataClientManager &dataClientManager, QWidget *parent)
    :QCheckBox(parent),
      DataClient(dataClientManager)
{

}

void DCCheckBox::setValueList(const Request& /*request*/, const QStringList& /*valueList*/,
                              const QStringList& /*rangeList*/, const QStringList& /*errorList*/)
{

}

void DCCheckBox::setStatusList(const Request &/*request*/, const QStringList &/*responseStatusList*/, const QStringList &/*responseErrorList*/)
{

}

void DCCheckBox::refresh()
{

}
