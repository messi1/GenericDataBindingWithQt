#ifndef DCLINEEDIT_H
#define DCLINEEDIT_H

#include <QLineEdit>
#include "DataBinding/DataClient.h"

class DCLineEdit : public QLineEdit, public DataClient
{
    Q_OBJECT
public:
    explicit DCLineEdit(IDataClientManager &dataClientManager, QWidget *parent = nullptr);
    void setValueList( const Request& request, const QStringList& valueList, const QStringList& rangeList) override;
    void setAccessRights(const QString& accessRights)override;
    void setErrorList(const Request& request, const QStringList& responseErrorList)override;
    void refresh() override;
};

#endif // DCLINEEDIT_H
