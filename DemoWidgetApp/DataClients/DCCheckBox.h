#ifndef DCCHECKBOX_H
#define DCCHECKBOX_H

#include <QCheckBox>
#include "DataBinding/DataClient.h"

class DCCheckBox : public QCheckBox, public DataClient
{
    Q_OBJECT
public:
    explicit DCCheckBox(IDataClientManager &dataClientManager, QWidget *parent = nullptr);
    void setValueList(const Request &request, const QStringList &valueList, const QStringList &rangeList) final;
    void setAccessRights(const QString &accessRights) final;
    void setErrorList(const Request &request, const QStringList &responseErrorList) final;
    void refresh() override;
};

#endif // DCCHECKBOX_H
