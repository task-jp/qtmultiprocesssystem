#ifndef QMPSAPPLICATIONFACTORY_H
#define QMPSAPPLICATIONFACTORY_H

#include "multiprocesssystem_global.h"
#include "qmpsapplication.h"

class QMpsApplicationManager;

class MULTIPROCESSSYSTEM_EXPORT QMpsApplicationFactory
{
public:
    static QList<QMpsApplication> apps(const QString &prefix);
    static QStringList keys();
    static QObject *load(const QString &key, QObject *parent = nullptr);
};

#endif // QMPSAPPLICATIONFACTORY_H
