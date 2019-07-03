#ifndef DCTEXTEDIT_H
#define DCTEXTEDIT_H

#include <QTextEdit>
#include "DataBinding/DataClient.h"

class DCTextEdit : public QTextEdit, public DataClient
{
    Q_OBJECT
public:
    explicit DCTextEdit(IDataClientManager& dataClientManager, QWidget *parent = nullptr);
    void setValueList( const Request& request, const QStringList& valueList, const QStringList& rangeList) override;
    void setAccessRights(const QString& accessRights)override;
    void setErrorList(const Request& request, const QStringList& responseErrorList)override;
    void refresh() override;
};

#endif // DCTEXTEDIT_H
