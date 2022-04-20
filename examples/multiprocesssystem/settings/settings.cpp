#include <QtMultiProcessSystem/qmpsapplicationplugin.h>

class Settings : public QMpsApplicationPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QMpsApplicationFactoryInterface_iid FILE "settings.json")
};

#include "settings.moc"
