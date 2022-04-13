#include "xdgshellwatchdog.h"

class XdgShellWatchDog::Private
{
public:
    QMap<uint, QMpsApplication> data;
};

XdgShellWatchDog::XdgShellWatchDog(QObject *parent)
    : QMpsWatchDog(parent)
    , d(new Private)
{}

XdgShellWatchDog::~XdgShellWatchDog() = default;

void XdgShellWatchDog::pingSent(const QMpsApplication &application, uint serial)
{
    d->data.insert(serial, application);
    ping(application, serial);
}

void XdgShellWatchDog::pongReceived(uint serial)
{
    pong(d->data.take(serial), serial);
}
