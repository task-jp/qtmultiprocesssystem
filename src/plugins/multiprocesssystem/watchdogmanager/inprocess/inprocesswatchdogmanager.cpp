#include "inprocesswatchdogmanager.h"

#include <QtCore/QReadWriteLock>
#include <QtCore/QTimer>

class InProcessWatchDogManager::Private
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

InProcessWatchDogManager::InProcessWatchDogManager(QObject *parent, Type type)
    : QMpsWatchDogManager(parent, type)
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

    connect(this, &InProcessWatchDogManager::finished, this, [this](const QMpsApplication &application) {
        QWriteLocker locker(&d->lock);
        for (int i = d->database.length() - 1; i >= 0 ; i--) {
            if (d->database.at(i).application == application)
                d->database.removeAt(i);
        }
    });

    connect(this, &InProcessWatchDogManager::pingReceived, this, [this](const QString &method, const QMpsApplication &application, uint serial) {
        QWriteLocker locker(&d->lock);
        d->database.append({method, application, serial});
        if (!d->timer.isActive())
            d->timer.start();
    });

    connect(this, &InProcessWatchDogManager::pongReceived, this, [this](const QString &method, const QMpsApplication &application, uint serial) {
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
    });

    connect(this, &InProcessWatchDogManager::pangReceived, this, [this](const QString &method, const QMpsApplication &application) {
        QWriteLocker locker(&d->lock);
        for (int i = 0; i < d->database.length(); i++) {
            const auto &ping = d->database.at(i);
            if (ping.method != method) continue;
            if (ping.application != application) continue;
            if (ping.serial > 0) continue;
            d->database[i].dateTime = QDateTime::currentDateTime();
            return;
        }

        d->database.append({method, application});
        if (!d->timer.isActive())
            d->timer.start();
    });
}

InProcessWatchDogManager::~InProcessWatchDogManager() = default;
