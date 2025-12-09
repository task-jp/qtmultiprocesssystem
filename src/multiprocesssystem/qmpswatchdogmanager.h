#ifndef QMPSWATCHDOGMANAGER_H
#define QMPSWATCHDOGMANAGER_H

#include <QtMultiProcessSystem/multiprocesssystem_global.h>
#include <QtMultiProcessSystem/qmpsipcinterface.h>
#include <QtMultiProcessSystem/qmpsapplication.h>

QT_BEGIN_NAMESPACE

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

QT_END_NAMESPACE

#endif // QMPSWATCHDOGMANAGER_H
