#include "qmpswatchdog.h"
#include "qmpswatchdogmanager.h"

class QMpsWatchDog::Private
{
public:
    QMpsWatchDogManager *watchDogManager = nullptr;
    QString method;
};

QMpsWatchDog::QMpsWatchDog(QObject *parent)
    : QObject(parent)
    , d(new Private)
{}

QMpsWatchDog::~QMpsWatchDog() = default;

QMpsWatchDogManager *QMpsWatchDog::watchDogManager() const
{
    return d->watchDogManager;
}

void QMpsWatchDog::setWatchDogManager(QMpsWatchDogManager *watchDogManager)
{
    if (d->watchDogManager == watchDogManager) return;
    d->watchDogManager = watchDogManager;
    emit watchDogManagerChanged(watchDogManager);
}

QString QMpsWatchDog::method() const
{
    return d->method;
}

void QMpsWatchDog::setMethod(const QString &method)
{
    if (d->method == method) return;
    d->method = method;
    emit methodChanged(method);
}

void QMpsWatchDog::ping(const QMpsApplication &app, uint serial)
{
    if (!d->watchDogManager) return;
    d->watchDogManager->ping(d->method, app, serial);
}

void QMpsWatchDog::pong(const QMpsApplication &app, uint serial)
{
    if (!d->watchDogManager) return;
    d->watchDogManager->pong(d->method, app, serial);
}

void QMpsWatchDog::pang(const QMpsApplication &app)
{
    if (!d->watchDogManager) return;
    d->watchDogManager->pang(d->method, app);
}
