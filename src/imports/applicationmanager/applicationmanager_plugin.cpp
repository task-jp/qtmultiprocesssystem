#include <QtQml/QQmlExtensionPlugin>

class ApplicationManagerPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)
public:
    explicit ApplicationManagerPlugin(QObject *parent = nullptr);
    void registerTypes(const char *uri) override;
};

ApplicationManagerPlugin::ApplicationManagerPlugin(QObject *parent)
    : QQmlExtensionPlugin(parent)
{}


void ApplicationManagerPlugin::registerTypes(const char *uri)
{
    Q_UNUSED(uri)
}

#include "applicationmanager_plugin.moc"
