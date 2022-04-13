#include "xdgshellwatchdog.h"
#include <QtMultiProcessSystem/QMpsWatchDog>

class XdgShellWatchDog::Private
{
public:
    QMpsWatchDog watchDog = QMpsWatchDog("xdg-shell");
    QMap<uint, QMpsApplication> data;
};

XdgShellWatchDog::XdgShellWatchDog(QObject *parent)
    : QObject(parent)
    , d(new Private)
{}

XdgShellWatchDog::~XdgShellWatchDog() = default;

void XdgShellWatchDog::ping(const QMpsApplication &application, uint serial)
{
    d->data.insert(serial, application);
    d->watchDog.ping(application, serial);
}

void XdgShellWatchDog::pong(uint serial)
{
    d->watchDog.pong(d->data.take(serial), serial);
}
