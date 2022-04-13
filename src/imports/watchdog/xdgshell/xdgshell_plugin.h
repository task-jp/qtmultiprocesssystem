#ifndef XDGSHELL_PLUGIN_H
#define XDGSHELL_PLUGIN_H

#include <QtQml/QQmlExtensionPlugin>

class XdgShellPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)
public:
    explicit XdgShellPlugin(QObject *parent = nullptr);
    void registerTypes(const char *uri) override;
};

#endif // XDGSHELL_PLUGIN_H
