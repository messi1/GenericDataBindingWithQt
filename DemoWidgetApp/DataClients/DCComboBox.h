#ifndef DCCOMBOBOX_H
#define DCCOMBOBOX_H

#include <QComboBox>
#include "DataBinding/DataClient.h"

class DCComboBox final: public QComboBox, public DataClient
{
    Q_OBJECT
public:
    explicit DCComboBox(IDataClientManager &dataClientManager, QWidget *parent = nullptr);
    void setValueList( const Request& request, const QStringList& valueList, const QStringList& rangeList) override;
    void setAccessRights(const QString& accessRights)override;
    void setErrorList(const Request& request, const QStringList& responseErrorList)override;
    void refresh() override;

};

#endif // DCCOMBOBOX_H
