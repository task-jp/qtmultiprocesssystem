#ifndef QMPSWINDOWMANAGERFACTORY_H
#define QMPSWINDOWMANAGERFACTORY_H

#include "qmpsabstractmanagerfactory.h"

class QMpsWindowManager;

class MULTIPROCESSSYSTEM_EXPORT QMpsWindowManagerFactory : public QMpsAbstractManagerFactory
{
public:
    static QStringList keys();
    static QMpsWindowManager *create(const QString &key, Type type, QObject *parent = nullptr);
};

#endif // QMPSWINDOWMANAGERFACTORY_H
