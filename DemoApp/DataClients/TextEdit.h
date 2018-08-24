#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QTextEdit>
#include "DataBinding/DataClient.h"

class TextEdit : public QTextEdit, public DataClient
{
    Q_OBJECT
public:
    explicit TextEdit(IDataClientManager& dataClientManager, QWidget *parent = nullptr);
    void setValue(     const RequestCmd requestCmd, const QString&     requestValue, const QString& requestRange, const int status) override;
    void setValue(     const RequestCmd requestCmd, const QString&     requestValue) override;
    void setValueList( const RequestCmd requestCmd, const QStringList& requestValueList) override;
    void setStatus(    const RequestCmd requestCmd, const QString&     requestError, const int status) override;
    void refresh() override;
};

#endif // TEXTEDIT_H
