#ifndef DCLABEL_H
#define DCLABEL_H

#include <QLabel>
#include "DataBinding/DataClient.h"

class DCLabel : public QLabel, public DataClient
{
    Q_OBJECT
public:
    explicit DCLabel(IDataClientManager &dataClientManager, QWidget *parent = nullptr);
    void setValueList( const Request& request, const QStringList& valueList, const QStringList& rangeList, const QStringList& errorList) override;
    void refresh() override;
};

#endif // DCLABEL_H
