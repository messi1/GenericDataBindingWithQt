#ifndef BASEFRAME_H
#define BASEFRAME_H

#include <QFrame>

#include "DataBinding/DataClientManager.h"

class BaseFrame : public QFrame, public DataClientManager
{
    Q_OBJECT
public:
    explicit BaseFrame(const QSharedPointer<IDataProxy> &dataProxyPtr, QWidget *parent = nullptr);
    ~BaseFrame()override = default;

protected:
    virtual void showEvent(QShowEvent *event) override;

};

#endif // BASEFRAME_H
