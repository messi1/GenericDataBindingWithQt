#ifndef DCCHECKBOX_H
#define DCCHECKBOX_H

#include <QCheckBox>
#include "DataBinding/DataClient.h"

class DCCheckBox : public QCheckBox, public DataClient
{
    Q_OBJECT
public:
    explicit DCCheckBox(IDataClientManager &dataClientManager, QWidget *parent = nullptr);
    void setValue(     const RequestCmd requestCmd, const QString&     requestValue, const QString& requestRange, const int status) override;
    void setValue(     const RequestCmd requestCmd, const QString&     requestValue) override;
    void setValueList( const RequestCmd requestCmd, const QStringList& requestValueList) override;
    void setStatus(    const RequestCmd requestCmd, const QString&     requestError, const int status) override;
    void refresh() override;
};

#endif // DCCHECKBOX_H
