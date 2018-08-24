#ifndef LABEL_H
#define LABEL_H

#include <QLabel>
#include "DataBinding/DataClient.h"

class Label : public QLabel, public DataClient
{
    Q_OBJECT
public:
    explicit Label(IDataClientManager &dataClientManager, QWidget *parent = nullptr);
    void setValue(     const RequestCmd requestCmd, const QString&     requestValue, const QString& requestRange, const int status) override;
    void setValue(     const RequestCmd requestCmd, const QString&     requestValue) override;
    void setValueList( const RequestCmd requestCmd, const QStringList& requestValueList) override;
    void setStatus(    const RequestCmd requestCmd, const QString&     requestError, const int status) override;
    void refresh() override;
};

#endif // LABEL_H
