#ifndef DCCOMBOBOX_H
#define DCCOMBOBOX_H

#include <QComboBox>
#include "DataBinding/DataClient.h"

class DCComboBox final: public QComboBox, public DataClient
{
    Q_OBJECT
public:
    explicit DCComboBox(IDataClientManager &dataClientManager, QWidget *parent = nullptr);
    void setValueList( const Request& request, const QStringList& valueList, const QStringList& rangeList, const QStringList& errorList) override;
    void refresh() override;

};

#endif // DCCOMBOBOX_H
