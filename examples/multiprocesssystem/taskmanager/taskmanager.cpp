#include <QtMultiProcessSystem/qmpsapplicationplugin.h>

class TaskManager : public QMpsApplicationPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QMpsApplicationFactoryInterface_iid FILE "taskmanager.json")
};

#include "taskmanager.moc"
