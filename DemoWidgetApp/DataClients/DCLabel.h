#ifndef DCLABEL_H
#define DCLABEL_H

#include <QLabel>
#include "DataBinding/DataClient.h"

class DCLabel : public QLabel, public DataClient
{
    Q_OBJECT
public:
    explicit DCLabel(IDataClientManager &dataClientManager, QWidget *parent = nullptr);
    virtual void setAccessRights(const QString &accessRights) override;
    virtual void setValueList(const Request &request,
                              const QStringList &responseValueList,
                              const QStringList &responseRangeList) override;
    virtual void setErrorList(const Request &request,
                              const QStringList &responseErrorList) override;
    void refresh() override;
};

#endif // DCLABEL_H
