#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <QComboBox>
#include "DataBinding/DataClient.h"

class ComboBox final: public QComboBox, public DataClient
{
    Q_OBJECT
public:
    explicit ComboBox(IDataClientManager &dataClientManager, QWidget *parent = nullptr);
    void setValue(     const RequestCmd requestCmd, const QString&     requestValue, const QString& requestRange, const int status) override;
    void setValue(     const RequestCmd requestCmd, const QString&     requestValue) override;
    void setValueList( const RequestCmd requestCmd, const QStringList& requestValueList) override;
    void setStatus(    const RequestCmd requestCmd, const QString&     requestError, const int status) override;
    void refresh() override;

};

#endif // COMBOBOX_H
