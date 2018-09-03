#include "DCComboBox.h"

DCComboBox::DCComboBox(IDataClientManager &dataClientManager, QWidget *parent)
    :QComboBox(parent),
      DataClient (dataClientManager)
{

}
void DCComboBox::setValueList(const Request& /*request*/, const QStringList& /*valueList*/,
                              const QStringList& /*rangeList*/, const QStringList& /*errorList*/)
{

}

void DCComboBox::setStatusList(const Request &/*request*/, const QStringList &/*responseStatusList*/, const QStringList &/*responseErrorList*/)
{

}

void DCComboBox::refresh()
{

}
