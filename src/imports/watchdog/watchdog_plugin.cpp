#include "watchdog_plugin.h"

WatchDogPlugin::WatchDogPlugin(QObject *parent)
    : QQmlExtensionPlugin(parent)
{}


void WatchDogPlugin::registerTypes(const char *uri)
{
    Q_UNUSED(uri)
}
