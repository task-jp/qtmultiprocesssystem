#ifndef QMPSWATCHDOGMANAGER_H
#define QMPSWATCHDOGMANAGER_H

#include "multiprocesssystem_global.h"
#include "qmpsipcinterface.h"
#include "qmpsapplication.h"

class MULTIPROCESSSYSTEM_EXPORT QMpsWatchDogManager : public QMpsIpcInterface
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "local.WatchDogManager")
public:
    explicit QMpsWatchDogManager(QObject *parent = nullptr, Type type = Client);
    ~QMpsWatchDogManager() override;

public Q_SLOTS:
    void ping(const QString &method, const QMpsApplication &application, uint serial);
    void pong(const QString &method, const QMpsApplication &application, uint serial);
    void pang(const QString &method, const QMpsApplication &application);

Q_SIGNALS:
    void started(const QMpsApplication &application);
    void finished(const QMpsApplication &application);
    void pingReceived(const QString &method, const QMpsApplication &application, uint serial);
    void pongReceived(const QString &method, const QMpsApplication &application, uint serial);
    void pangReceived(const QString &method, const QMpsApplication &application);
    void inactiveChanged(const QString &method, const QMpsApplication &application, bool inactive, int msecs);

protected:
    QMpsAbstractIpcInterface *server() const override;

private:
    class Private;
    QScopedPointer<Private> d;
};

#endif // QMPSWATCHDOGMANAGER_H
