#ifndef QMPSWATCHDOGMANAGERFACTORY_H
#define QMPSWATCHDOGMANAGERFACTORY_H

#include "qmpsabstractmanagerfactory.h"

class QObject;
class QMpsWatchDogManager;

class MULTIPROCESSSYSTEM_EXPORT QMpsWatchDogManagerFactory : public QMpsAbstractManagerFactory
{
public:
    static QStringList keys();
    static QMpsWatchDogManager *create(const QString &key, QObject *parent = nullptr, Type type = Client);
};

#endif // QMPSWATCHDOGMANAGERFACTORY_H
