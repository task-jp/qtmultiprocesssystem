#include <QtMultiProcessSystem/qmpsapplicationmanagerplugin.h>

#include "remoteobjectsapplicationmanager.h"

class QRemoteObjectsApplicationManagerPlugin : public QMpsApplicationManagerPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QMpsApplicationManagerFactoryInterface_iid FILE "remoteobjects.json")
public:
    QMpsApplicationManager *create(const QString &key, QMpsAbstractManagerFactory::Type type, QObject *parent = nullptr) override
    {
        if (!key.compare(QLatin1String("remoteobjects"), Qt::CaseInsensitive)) {
            switch (type) {
            case QMpsAbstractManagerFactory::Server:
                return new RemoteObjectsApplicationManagerServer(parent);
            case QMpsAbstractManagerFactory::Client:
                return new RemoteObjectsApplicationManagerClient(parent);
            default:
                break;
            }
        }

        return nullptr;
    }
};

#include "main.moc"
