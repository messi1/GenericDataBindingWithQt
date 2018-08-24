#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QPushButton>
#include "DataBinding/DataClient.h"

class PushButton : public QPushButton, public DataClient
{
    Q_OBJECT
public:
    explicit PushButton(IDataClientManager &dataClientManager, QWidget *parent = nullptr);
    void setValue(     const RequestCmd requestCmd, const QString&     requestValue, const QString& requestRange, const int status) override;
    void setValue(     const RequestCmd requestCmd, const QString&     requestValue) override;
    void setValueList( const RequestCmd requestCmd, const QStringList& requestValueList) override;
    void setStatus(    const RequestCmd requestCmd, const QString&     requestError, const int status) override;
    void refresh() override;
};

#endif // PUSHBUTTON_H
