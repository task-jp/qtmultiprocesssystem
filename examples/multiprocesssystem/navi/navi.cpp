#include <QtMultiProcessSystem/qmpsapplicationplugin.h>

class Navi : public QMpsApplicationPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QMpsApplicationFactoryInterface_iid FILE "navi.json")
};

#include "navi.moc"
