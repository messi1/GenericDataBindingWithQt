#ifndef DCTEXTEDIT_H
#define DCTEXTEDIT_H

#include <QTextEdit>
#include "DataBinding/DataClient.h"

class DCTextEdit : public QTextEdit, public DataClient
{
    Q_OBJECT
public:
    explicit DCTextEdit(IDataClientManager& dataClientManager, QWidget *parent = nullptr);
    void setValue(     const RequestCmd requestCmd, const QString&     requestValue, const QString& requestRange, const int status) override;
    void setValue(     const RequestCmd requestCmd, const QString&     requestValue) override;
    void setValueList( const RequestCmd requestCmd, const QStringList& requestValueList) override;
    void setStatus(    const RequestCmd requestCmd, const QString&     requestError, const int status) override;
    void refresh() override;
};

#endif // DCTEXTEDIT_H
