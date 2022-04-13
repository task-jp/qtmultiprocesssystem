#include "remoteobjectswatchdogmanager.h"

#include <QtCore/QReadWriteLock>
#include <QtCore/QTimer>

class WatchDogManager::Private
{
public:
    struct Ping {
        QString method;
        QMpsApplication application;
        uint serial = 0;
        QDateTime dateTime = QDateTime::currentDateTime();
    };
    QReadWriteLock lock;
    QList<Ping> database;
    QTimer timer;
    QHash<QMpsApplication, QDateTime> sleeping;
};

WatchDogManager::WatchDogManager(QObject *parent)
    : WatchDogManagerSimpleSource(parent)
    , d(new Private)
{
    d->timer.setInterval(250);
    connect(&d->timer, &QTimer::timeout, [this]() {
        QReadLocker locker(&d->lock);
        const auto now = QDateTime::currentDateTime();
        for (int i = 0; i < d->database.length(); i++) {
            const auto &ping = d->database.at(i);
            const auto diff = ping.dateTime.msecsTo(now);
            if (diff > 1000) {
                if (!d->sleeping.contains(ping.application)) {
                    d->sleeping.insert(ping.application, ping.dateTime);
                    emit inactiveChanged(ping.method, ping.application, true, ping.dateTime.msecsTo(now));
                    qWarning() << ping.application.key() << ping.method << diff << ping.serial;
                }
            }
        }
    });
}

WatchDogManager::~WatchDogManager() = default;

void WatchDogManager::started(const QMpsApplication &application)
{
    Q_UNUSED(application);
}

void WatchDogManager::finished(const QMpsApplication &application)
{
    QWriteLocker locker(&d->lock);
    for (int i = d->database.length() - 1; i >= 0 ; i--) {
        if (d->database.at(i).application == application)
            d->database.removeAt(i);
    }
}

void WatchDogManager::ping(const QString &method, const QMpsApplication &application, uint serial)
{
    QWriteLocker locker(&d->lock);
    d->database.append({method, application, serial});
    if (!d->timer.isActive())
        d->timer.start();
}

void WatchDogManager::pong(const QString &method, const QMpsApplication &application, uint serial)
{
    QWriteLocker locker(&d->lock);
    for (int i = 0; i < d->database.length(); i++) {
        const auto &ping = d->database.at(i);
        if (ping.method != method) continue;
        if (ping.application != application) continue;
        if (ping.serial != serial) continue;
        d->database.removeAt(i);
        if (d->database.isEmpty())
            d->timer.stop();

        if (d->sleeping.contains(application)) {
            emit inactiveChanged(method, application, false, d->sleeping.take(application).msecsTo(QDateTime::currentDateTime()));
        }
        return;
    }
    qWarning() << method << serial << "not found";
}

void WatchDogManager::pang(const QString &method, const QMpsApplication &application)
{
    QWriteLocker locker(&d->lock);
    for (int i = 0; i < d->database.length(); i++) {
        const auto &ping = d->database.at(i);
        if (ping.method != method) continue;
        if (ping.application != application) continue;
        if (ping.serial > 0) continue;
        d->database[i].dateTime = QDateTime::currentDateTime();
        if (d->sleeping.contains(application)) {
            emit inactiveChanged(method, application, false, d->sleeping.take(application).msecsTo(QDateTime::currentDateTime()));
        }
        return;
    }

    d->database.append({method, application});
    if (!d->timer.isActive())
        d->timer.start();
}

RemoteObjectsWatchDogManagerServer::RemoteObjectsWatchDogManagerServer(QObject *parent)
    : QMpsWatchDogManager(parent)
{
    auto host = new QRemoteObjectHost(QUrl(QStringLiteral("local:app2")), this);
    host->enableRemoting(&source);
    connect(&source, &WatchDogManager::inactiveChanged, this, &RemoteObjectsWatchDogManagerServer::inactiveChanged);
}

void RemoteObjectsWatchDogManagerServer::started(const QMpsApplication &application)
{
    source.started(application);
}

void RemoteObjectsWatchDogManagerServer::finished(const QMpsApplication &application)
{
    source.finished(application);
}

void RemoteObjectsWatchDogManagerServer::ping(const QString &method, const QMpsApplication &application, uint serial)
{
    source.ping(method, application, serial);
}

void RemoteObjectsWatchDogManagerServer::pong(const QString &method, const QMpsApplication &application, uint serial)
{
    source.pong(method, application, serial);
}

void RemoteObjectsWatchDogManagerServer::pang(const QString &method, const QMpsApplication &application)
{
    source.pang(method, application);
}

RemoteObjectsWatchDogManagerClient::RemoteObjectsWatchDogManagerClient(QObject *parent)
    : QMpsWatchDogManager(parent)
{
    auto node = new QRemoteObjectNode(this);
    node->connectToNode(QUrl(QStringLiteral("local:app2")));
    replica.setNode(node);
    connect(&replica, &WatchDogManagerReplica::inactiveChanged, this, &RemoteObjectsWatchDogManagerClient::inactiveChanged);
}

void RemoteObjectsWatchDogManagerClient::started(const QMpsApplication &application)
{
    replica.started(application);
}

void RemoteObjectsWatchDogManagerClient::finished(const QMpsApplication &application)
{
    replica.finished(application);
}

void RemoteObjectsWatchDogManagerClient::ping(const QString &method, const QMpsApplication &application, uint serial)
{
    replica.ping(method, application, serial);
}

void RemoteObjectsWatchDogManagerClient::pong(const QString &method, const QMpsApplication &application, uint serial)
{
    replica.pong(method, application, serial);
}

void RemoteObjectsWatchDogManagerClient::pang(const QString &method, const QMpsApplication &application)
{
    replica.pang(method, application);
}
