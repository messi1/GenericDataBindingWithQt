#ifndef LINEEDIT_H
#define LINEEDIT_H

#include <QLineEdit>
#include "DataBinding/DataClient.h"

class LineEdit : public QLineEdit, public DataClient
{
    Q_OBJECT
public:
    explicit LineEdit(IDataClientManager &dataClientManager, QWidget *parent = nullptr);
    void setValue(     const RequestCmd requestCmd, const QString&     requestValue, const QString& requestRange, const int status) override;
    void setValue(     const RequestCmd requestCmd, const QString&     requestValue) override;
    void setValueList( const RequestCmd requestCmd, const QStringList& requestValueList) override;
    void setStatus(    const RequestCmd requestCmd, const QString&     requestError, const int status) override;
    void refresh() override;
};

#endif // LINEEDIT_H
