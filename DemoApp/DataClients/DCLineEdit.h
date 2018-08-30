#ifndef DCLINEEDIT_H
#define DCLINEEDIT_H

#include <QLineEdit>
#include "DataBinding/DataClient.h"

class DCLineEdit : public QLineEdit, public DataClient
{
    Q_OBJECT
public:
    explicit DCLineEdit(IDataClientManager &dataClientManager, QWidget *parent = nullptr);
    void setValueList( const Request& request, const QStringList& valueList, const QStringList& rangeList, const QStringList& errorList) override;
    void refresh() override;
};

#endif // DCLINEEDIT_H
