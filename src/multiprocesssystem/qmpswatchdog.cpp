#include "qmpswatchdog.h"
#include "qmpswatchdogmanager.h"

QMpsWatchDog::QMpsWatchDog(const QString &method, QObject *parent)
    : QObject(parent)
    , method(method)
{}

void QMpsWatchDog::ping(const QMpsApplication &app, uint serial)
{
    if (!QMpsWatchDogManager::instance()) return;
    QMpsWatchDogManager::instance()->ping(method, app, serial);
}

void QMpsWatchDog::pong(const QMpsApplication &app, uint serial)
{
    if (!QMpsWatchDogManager::instance()) return;
    QMpsWatchDogManager::instance()->pong(method, app, serial);
}

void QMpsWatchDog::pang(const QMpsApplication &app)
{
    if (!QMpsWatchDogManager::instance()) return;
    QMpsWatchDogManager::instance()->pang(method, app);
}
