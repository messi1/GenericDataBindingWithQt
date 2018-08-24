#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <QCheckBox>
#include "DataBinding/DataClient.h"

class CheckBox : public QCheckBox, public DataClient
{
    Q_OBJECT
public:
    explicit CheckBox(IDataClientManager &dataClientManager, QWidget *parent = nullptr);
    void setValue(     const RequestCmd requestCmd, const QString&     requestValue, const QString& requestRange, const int status) override;
    void setValue(     const RequestCmd requestCmd, const QString&     requestValue) override;
    void setValueList( const RequestCmd requestCmd, const QStringList& requestValueList) override;
    void setStatus(    const RequestCmd requestCmd, const QString&     requestError, const int status) override;
    void refresh() override;
};

#endif // CHECKBOX_H
