#ifndef DCCOMPONENT_H
#define DCCOMPONENT_H

#include <QObject>

#include "DataBinding/DataClientManager.h"

class DCComponent : public QObject, public DataClientManager
{
    Q_OBJECT
public:
    DCComponent();
    explicit DCComponent(IDataProxy& dataProxy, QObject *parent = nullptr);

signals:

public slots:
};

#endif // DCCOMPONENT_H
