#include "qmpsinprocesswatchdogmanager.h"

#include <QtCore/QReadWriteLock>
#include <QtCore/QTimer>

class QMpsInProcessWatchDogManager::Private
{
public:
    struct Ping {
        QString method;
        QMpsApplication application;
        uint serial;
        QDateTime dateTime = QDateTime::currentDateTime();
    };
    QReadWriteLock lock;
    QList<Ping> database;
    QTimer timer;
};


QMpsInProcessWatchDogManager::QMpsInProcessWatchDogManager(QObject *parent)
    : QMpsWatchDogManager(parent)
    , d(new Private)
{
    d->timer.setInterval(250);
    connect(&d->timer, &QTimer::timeout, [this]() {
        QReadLocker locker(&d->lock);
        const auto now = QDateTime::currentDateTime();
        qDebug() << d->database.length();
        for (int i = 0; i < d->database.length(); i++) {
            const auto &ping = d->database.at(i);
            const auto diff = ping.dateTime.msecsTo(now);
            if (diff > 1000) {
                qWarning() << ping.application.key() << ping.method << diff << ping.serial;
            }
        }
    });
}

QMpsInProcessWatchDogManager::~QMpsInProcessWatchDogManager() = default;

void QMpsInProcessWatchDogManager::started(const QMpsApplication &application)
{
    Q_UNUSED(application);
}

void QMpsInProcessWatchDogManager::finished(const QMpsApplication &application)
{
    QWriteLocker locker(&d->lock);
    for (int i = d->database.length() - 1; i >= 0 ; i--) {
        if (d->database.at(i).application == application)
            d->database.removeAt(i);
    }
}

void QMpsInProcessWatchDogManager::pingSent(const QString &method, const QMpsApplication &application, uint serial)
{
    QWriteLocker locker(&d->lock);
    d->database.append({method, application, serial});
    if (!d->timer.isActive())
        d->timer.start();
}

void QMpsInProcessWatchDogManager::pongReceived(const QString &method, uint serial)
{
    QWriteLocker locker(&d->lock);
    for (int i = 0; i < d->database.length(); i++) {
        const auto &ping = d->database.at(i);
        if (ping.method != method) continue;
        if (ping.serial != serial) continue;
        const auto diff = ping.dateTime.msecsTo(QDateTime::currentDateTime());
        qDebug() << ping.application.key() << method << diff;
        d->database.removeAt(i);
        if (d->database.isEmpty())
            d->timer.stop();
        return;
    }
    locker.unlock();
    qWarning() << method << serial << "not found";
}
