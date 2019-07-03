#include "DCComboBox.h"

DCComboBox::DCComboBox(IDataClientManager &dataClientManager, QWidget *parent)
    :QComboBox(parent),
      DataClient (dataClientManager)
{

}
void DCComboBox::setValueList(const Request& /*request*/, const QStringList& /*valueList*/,
                              const QStringList& /*rangeList*/)
{

}

void DCComboBox::setAccessRights(const QString &/*accessRights*/)
{

}

void DCComboBox::setErrorList(const Request &/*request*/, const QStringList &/*responseErrorList*/)
{

}

void DCComboBox::refresh()
{

}
