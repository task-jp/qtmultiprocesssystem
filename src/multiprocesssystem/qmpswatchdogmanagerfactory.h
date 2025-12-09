#ifndef QMPSWATCHDOGMANAGERFACTORY_H
#define QMPSWATCHDOGMANAGERFACTORY_H

#include <QtMultiProcessSystem/qmpsabstractmanagerfactory.h>

QT_BEGIN_NAMESPACE

class QObject;
class QMpsWatchDogManager;

class MULTIPROCESSSYSTEM_EXPORT QMpsWatchDogManagerFactory : public QMpsAbstractManagerFactory
{
public:
    static QStringList keys();
    static QMpsWatchDogManager *create(const QString &key, QObject *parent = nullptr, Type type = Client);
};

QT_END_NAMESPACE

#endif // QMPSWATCHDOGMANAGERFACTORY_H
