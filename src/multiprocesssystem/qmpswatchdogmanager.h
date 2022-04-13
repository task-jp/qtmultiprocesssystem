#ifndef QMPSWATCHDOGMANAGER_H
#define QMPSWATCHDOGMANAGER_H

#include "multiprocesssystem_global.h"
#include <QtCore/QObject>
#include "qmpsapplication.h"

class MULTIPROCESSSYSTEM_EXPORT QMpsWatchDogManager : public QObject
{
    Q_OBJECT
public:
    static QMpsWatchDogManager *instance();
    explicit QMpsWatchDogManager(QObject *parent = nullptr);

public Q_SLOTS:
    virtual void started(const QMpsApplication &application) = 0;
    virtual void finished(const QMpsApplication &application) = 0;
    virtual void pingSent(const QString &method, const QMpsApplication &application, uint serial) = 0;
    virtual void pongReceived(const QString &method, uint serial) = 0;
};

#endif // QMPSWATCHDOGMANAGER_H
