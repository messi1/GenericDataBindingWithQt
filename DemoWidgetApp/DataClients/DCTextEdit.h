#ifndef DCTEXTEDIT_H
#define DCTEXTEDIT_H

#include <QTextEdit>
#include "DataBinding/DataClient.h"

class DCTextEdit : public QTextEdit, public DataClient
{
    Q_OBJECT
public:
    explicit DCTextEdit(IDataClientManager& dataClientManager, QWidget *parent = nullptr);
    void setValueList( const Request& request, const QStringList& valueList, const QStringList& rangeList, const QStringList& errorList) override;
    void setStatusList(const Request& request, const QStringList& responseStatusList, const QStringList& responseErrorList) override;
    void refresh() override;
};

#endif // DCTEXTEDIT_H
