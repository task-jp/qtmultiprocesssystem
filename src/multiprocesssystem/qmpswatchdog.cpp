#include "qmpswatchdog.h"
#include "qmpswatchdogmanager.h"

QMpsWatchDog::QMpsWatchDog(QObject *parent)
    : QObject(parent)
{}

void QMpsWatchDog::ping(const QMpsApplication &app, uint serial)
{
    QMpsWatchDogManager::instance()->ping(method(), app, serial);
}

void QMpsWatchDog::pong(const QMpsApplication &app, uint serial)
{
    QMpsWatchDogManager::instance()->pong(method(), app, serial);
}

void QMpsWatchDog::pang(const QMpsApplication &app)
{
    QMpsWatchDogManager::instance()->pang(method(), app);
}
