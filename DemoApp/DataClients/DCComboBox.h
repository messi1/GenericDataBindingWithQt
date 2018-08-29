#ifndef DCCOMBOBOX_H
#define DCCOMBOBOX_H

#include <QComboBox>
#include "DataBinding/DataClient.h"

class DCComboBox final: public QComboBox, public DataClient
{
    Q_OBJECT
public:
    explicit DCComboBox(IDataClientManager &dataClientManager, QWidget *parent = nullptr);
    void setValue(     const RequestCmd requestCmd, const QString&     requestValue, const QString& requestRange, const int status) override;
    void setValue(     const RequestCmd requestCmd, const QString&     requestValue) override;
    void setValueList( const RequestCmd requestCmd, const QStringList& requestValueList) override;
    void setStatus(    const RequestCmd requestCmd, const QString&     requestError, const int status) override;
    void refresh() override;

};

#endif // DCCOMBOBOX_H
