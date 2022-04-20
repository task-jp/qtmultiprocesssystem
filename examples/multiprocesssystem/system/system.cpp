#include <QtMultiProcessSystem/qmpsapplicationplugin.h>

class System : public QMpsApplicationPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QMpsApplicationFactoryInterface_iid FILE "system.json")
};

#include "system.moc"
