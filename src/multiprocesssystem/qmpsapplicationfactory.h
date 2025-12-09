#ifndef QMPSAPPLICATIONFACTORY_H
#define QMPSAPPLICATIONFACTORY_H

#include <QtMultiProcessSystem/multiprocesssystem_global.h>
#include <QtMultiProcessSystem/qmpsapplication.h>

QT_BEGIN_NAMESPACE

class QMpsApplicationManager;

class MULTIPROCESSSYSTEM_EXPORT QMpsApplicationFactory
{
public:
    static QList<QMpsApplication> apps(const QString &prefix);
    static QStringList keys();
    static QObject *load(const QString &key, QObject *parent = nullptr);
};

QT_END_NAMESPACE

#endif // QMPSAPPLICATIONFACTORY_H
