#include "xdgshell_plugin.h"

XdgShellPlugin::XdgShellPlugin(QObject *parent)
    : QQmlExtensionPlugin(parent)
{}


void XdgShellPlugin::registerTypes(const char *uri)
{
    Q_UNUSED(uri)
}
