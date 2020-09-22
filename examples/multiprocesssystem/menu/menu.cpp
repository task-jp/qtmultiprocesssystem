#include <QtMultiProcessSystem/qmpsapplicationplugin.h>

class Menu : public QMpsApplicationPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QMpsApplicationFactoryInterface_iid FILE "menu.json")
};

#include "menu.moc"
