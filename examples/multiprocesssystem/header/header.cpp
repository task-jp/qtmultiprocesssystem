#include <QtMultiProcessSystem/qmpsapplicationplugin.h>

class Header : public QMpsApplicationPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QMpsApplicationFactoryInterface_iid FILE "header.json")
};

#include "header.moc"
