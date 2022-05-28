#include "systemdwatchdog.h"

#if QT_CONFIG(systemd_watchdog)
#include <systemd/sd-daemon.h>
#endif

class SystemdWatchDog::Private
{
public:
    bool enabled = false;
};

SystemdWatchDog::SystemdWatchDog(QObject *parent)
    : QObject(parent)
    , d(new Private)
{
#if !QT_CONFIG(systemd_watchdog)
    qWarning("SystemdWatchDog is not supported");
#else
    // WATCHDOG_USEC is set by systemd when WatchdogSec is set in its service-unit
    if (qEnvironmentVariableIsSet("WATCHDOG_USEC")) {
        qInfo("SystemdWatchDog is available");
        d->enabled = true;
    } else {
        qInfo("SystemdWatchDog is not available");
    }
#endif
}

SystemdWatchDog::~SystemdWatchDog() = default;

void SystemdWatchDog::pang()
{
#if QT_CONFIG(systemd_watchdog)
    if (d->enabled) {
        sd_notify(0, "WATCHDOG=1");
    }
#endif
}
