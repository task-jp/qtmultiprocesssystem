#ifndef WATCHDOG_PLUGIN_H
#define WATCHDOG_PLUGIN_H

#include <QtQml/QQmlExtensionPlugin>

class WatchDogPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)
public:
    explicit WatchDogPlugin(QObject *parent = nullptr);
    void registerTypes(const char *uri) override;
};

#endif // WATCHDOG_PLUGIN_H
