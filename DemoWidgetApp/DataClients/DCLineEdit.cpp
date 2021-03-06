#include "DCLineEdit.h"

DCLineEdit::DCLineEdit(IDataClientManager &dataClientManager, QWidget *parent)
    :QLineEdit(parent),
     DataClient (dataClientManager)
{

}

void DCLineEdit::setValueList(const Request& /*request*/, const QStringList& /*valueList*/,
                              const QStringList& /*rangeList*/)
{

}

void DCLineEdit::setAccessRights(const QString& accessRights)
{
  if(accessRights.isEmpty())
    this->setVisible(false);
  else
  {
    this->setVisible(true);

    if(accessRights.contains('r'))
      this->setEnabled(false);
    if(accessRights.contains('w'))
      this->setEnabled(true);
  }
}

void DCLineEdit::setErrorList(const Request &/*request*/, const QStringList &/*responseErrorList*/)
{

}

void DCLineEdit::refresh()
{

}
