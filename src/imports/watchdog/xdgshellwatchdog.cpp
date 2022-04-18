#include "xdgshellwatchdog.h"
#include <QtMultiProcessSystem/QMpsWatchDog>

class XdgShellWatchDog::Private
{
public:
    QMpsWatchDog watchDog;
    QMap<uint, QMpsApplication> data;
};

XdgShellWatchDog::XdgShellWatchDog(QObject *parent)
    : QObject(parent)
    , d(new Private)
{
    d->watchDog.setMethod("xdg-shell");
    connect(&d->watchDog, &QMpsWatchDog::watchDogManagerChanged, this, &XdgShellWatchDog::watchDogManagerChanged);
}

XdgShellWatchDog::~XdgShellWatchDog() = default;


QMpsWatchDogManager *XdgShellWatchDog::watchDogManager() const
{
    return d->watchDog.watchDogManager();
}

void XdgShellWatchDog::setWatchDogManager(QMpsWatchDogManager *watchDogManager)
{
    d->watchDog.setWatchDogManager(watchDogManager);
}

void XdgShellWatchDog::ping(const QMpsApplication &application, uint serial)
{
    d->data.insert(serial, application);
    d->watchDog.ping(application, serial);
}

void XdgShellWatchDog::pong(uint serial)
{
    d->watchDog.pong(d->data.take(serial), serial);
}
