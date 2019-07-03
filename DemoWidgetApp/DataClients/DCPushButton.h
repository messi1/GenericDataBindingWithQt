#ifndef DCPUSHBUTTON_H
#define DCPUSHBUTTON_H

#include <QPushButton>
#include "DataBinding/DataClient.h"

class DCPushButton : public QPushButton, public DataClient
{
    Q_OBJECT
public:
    explicit DCPushButton(IDataClientManager &dataClientManager, QWidget *parent = nullptr);
    void setValueList( const Request& request, const QStringList& valueList, const QStringList& rangeList) override;
    void setAccessRights(const QString& accessRights)override;
    void setErrorList(const Request& request, const QStringList& responseErrorList)override;
    void refresh() override;
};

#endif // DCPUSHBUTTON_H
