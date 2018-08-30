#ifndef DCPUSHBUTTON_H
#define DCPUSHBUTTON_H

#include <QPushButton>
#include "DataBinding/DataClient.h"

class DCPushButton : public QPushButton, public DataClient
{
    Q_OBJECT
public:
    explicit DCPushButton(IDataClientManager &dataClientManager, QWidget *parent = nullptr);
    void setValueList( const Request& request, const QStringList& valueList,
                       const QStringList& rangeList, const QStringList& errorList) override;
    void refresh() override;
};

#endif // DCPUSHBUTTON_H
