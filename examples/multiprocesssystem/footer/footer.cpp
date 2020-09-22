#include <QtMultiProcessSystem/qmpsapplicationplugin.h>

class Footer : public QMpsApplicationPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QMpsApplicationFactoryInterface_iid FILE "footer.json")
};

#include "footer.moc"
