#include "systemdwatchdog.h"

#if QT_CONFIG(systemd_watchdog)
#include <systemd/sd-daemon.h>
#endif

SystemdWatchDog::SystemdWatchDog(QObject *parent)
    : QObject(parent)
{
#if !QT_CONFIG(systemd_watchdog)
    qWarning("SystemdWatchDog is disabled");
#endif
}

void SystemdWatchDog::pang()
{
#if QT_CONFIG(systemd_watchdog)
    sd_notify(0, "WATCHDOG=1");
#endif
}
