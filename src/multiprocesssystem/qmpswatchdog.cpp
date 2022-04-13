#include "qmpswatchdog.h"
#include "qmpswatchdogmanager.h"

QMpsWatchDog::QMpsWatchDog(QObject *parent)
    : QObject(parent)
{}

void QMpsWatchDog::pingSentImpl(const QMpsApplication &app, uint serial)
{
    QMpsWatchDogManager::instance()->pingSent(method(), app, serial);
}

void QMpsWatchDog::pongReceivedImpl(uint serial)
{
    QMpsWatchDogManager::instance()->pongReceived(method(), serial);
}
