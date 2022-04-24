#include <QtQml/QQmlExtensionPlugin>
#include <QtMultiProcessSystem/QMpsUriHandler>
#include <QtQml/qqml.h>

class UriHandlerPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)
public:
    explicit UriHandlerPlugin(QObject *parent = nullptr);
    void registerTypes(const char *uri) override;
};

UriHandlerPlugin::UriHandlerPlugin(QObject *parent)
    : QQmlExtensionPlugin(parent)
{}


void UriHandlerPlugin::registerTypes(const char *uri)
{
    if (QStringLiteral("QtMultiProcessSystem.UriHandler") == uri) {
        qmlRegisterType<QMpsUriHandler>(uri, 1, 15, "UriHandler");
    }
}

#include "urihandler_plugin.moc"
