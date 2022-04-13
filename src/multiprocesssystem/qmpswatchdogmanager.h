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
    virtual void ping(const QString &method, const QMpsApplication &application, uint serial) = 0;
    virtual void pong(const QString &method, const QMpsApplication &application, uint serial) = 0;
    virtual void pang(const QString &method, const QMpsApplication &application) = 0;

Q_SIGNALS:
    void inactiveChanged(const QString &method, const QMpsApplication &application, bool inactive, int msecs);
};

#endif // QMPSWATCHDOGMANAGER_H
