#include <QtMultiProcessSystem/qmpsapplicationplugin.h>

class Radio : public QMpsApplicationPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QMpsApplicationFactoryInterface_iid FILE "radio.json")
};

#include "radio.moc"
