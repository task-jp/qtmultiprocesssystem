#include <QtMultiProcessSystem/qmpsapplicationplugin.h>

class Music : public QMpsApplicationPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QMpsApplicationFactoryInterface_iid FILE "music.json")
};

#include "music.moc"
