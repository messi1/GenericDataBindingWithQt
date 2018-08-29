#ifndef DCLINEEDIT_H
#define DCLINEEDIT_H

#include <QLineEdit>
#include "DataBinding/DataClient.h"

class DCLineEdit : public QLineEdit, public DataClient
{
    Q_OBJECT
public:
    explicit DCLineEdit(IDataClientManager &dataClientManager, QWidget *parent = nullptr);
    void setValue(     const RequestCmd requestCmd, const QString&     requestValue, const QString& requestRange, const int status) override;
    void setValue(     const RequestCmd requestCmd, const QString&     requestValue) override;
    void setValueList( const RequestCmd requestCmd, const QStringList& requestValueList) override;
    void setStatus(    const RequestCmd requestCmd, const QString&     requestError, const int status) override;
    void refresh() override;
};

#endif // DCLINEEDIT_H
