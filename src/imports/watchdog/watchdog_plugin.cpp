#include <QtQml/QQmlExtensionPlugin>

class WatchDogPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)
public:
    explicit WatchDogPlugin(QObject *parent = nullptr);
    void registerTypes(const char *uri) override;
};

WatchDogPlugin::WatchDogPlugin(QObject *parent)
    : QQmlExtensionPlugin(parent)
{}


void WatchDogPlugin::registerTypes(const char *uri)
{
    Q_UNUSED(uri)
}

#include "watchdog_plugin.moc"
