#include <QtMultiProcessSystem/qmpsapplicationmanagerplugin.h>

#include "systemdapplicationmanager.h"

class SystemdApplicationManagerPlugin : public QMpsApplicationManagerPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QMpsApplicationManagerFactoryInterface_iid FILE "systemd.json")
public:
    QMpsApplicationManager *create(const QString &key, QObject *parent, QMpsAbstractIpcInterface::Type type) override
    {
        if (!key.compare(QLatin1String("systemd"), Qt::CaseInsensitive)) {
            return new SystemdApplicationManager(parent, type);
        }

        return nullptr;
    }
};

#include "main.moc"
