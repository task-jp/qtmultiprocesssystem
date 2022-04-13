#ifndef REMOTEOBJECTSWATCHDOGMANAGER_H
#define REMOTEOBJECTSWATCHDOGMANAGER_H

#include <QtMultiProcessSystem/QMpsWatchDogManager>
#include "rep_watchdogmanager_merged.h"

class WatchDogManager : public WatchDogManagerSimpleSource
{
    Q_OBJECT
public:
    explicit WatchDogManager(QObject *parent = nullptr);
    ~WatchDogManager() override;

public Q_SLOTS:
    void started(const QMpsApplication &application) override;
    void finished(const QMpsApplication &application) override;
    void ping(const QString &method, const QMpsApplication &application, uint serial) override;
    void pong(const QString &method, const QMpsApplication &application, uint serial) override;
    void pang(const QString &method, const QMpsApplication &application) override;

private:
    class Private;
    QScopedPointer<Private> d;
};

class RemoteObjectsWatchDogManagerServer : public QMpsWatchDogManager
{
    Q_OBJECT
public:
    explicit RemoteObjectsWatchDogManagerServer(QObject *parent = nullptr);

public Q_SLOTS:
    void started(const QMpsApplication &application) override;
    void finished(const QMpsApplication &application) override;
    void ping(const QString &method, const QMpsApplication &application, uint serial) override;
    void pong(const QString &method, const QMpsApplication &application, uint serial) override;
    void pang(const QString &method, const QMpsApplication &application) override;

private:
    WatchDogManager source;
};

class RemoteObjectsWatchDogManagerClient : public QMpsWatchDogManager
{
    Q_OBJECT
public:
    explicit RemoteObjectsWatchDogManagerClient(QObject *parent = nullptr);

public Q_SLOTS:
    void started(const QMpsApplication &application) override;
    void finished(const QMpsApplication &application) override;
    void ping(const QString &method, const QMpsApplication &application, uint serial) override;
    void pong(const QString &method, const QMpsApplication &application, uint serial) override;
    void pang(const QString &method, const QMpsApplication &application) override;

private:
    WatchDogManagerReplica replica;
};

#endif // REMOTEOBJECTSWATCHDOGMANAGER_H
