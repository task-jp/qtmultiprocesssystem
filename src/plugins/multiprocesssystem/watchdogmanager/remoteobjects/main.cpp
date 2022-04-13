#include <QtMultiProcessSystem/qmpswatchdogmanagerplugin.h>

#include "remoteobjectswatchdogmanager.h"

class QRemoteObjectsWatchDogManagerPlugin : public QMpsWatchDogManagerPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QMpsWatchDogManagerFactoryInterface_iid FILE "remoteobjects.json")
public:
    QMpsWatchDogManager *create(const QString &key, QMpsAbstractManagerFactory::Type type, QObject *parent = nullptr) override
    {
        if (!key.compare(QLatin1String("remoteobjects"), Qt::CaseInsensitive)) {
            switch (type) {
            case QMpsAbstractManagerFactory::Server:
                return new RemoteObjectsWatchDogManagerServer(parent);
            case QMpsAbstractManagerFactory::Client:
                return new RemoteObjectsWatchDogManagerClient(parent);
            default:
                break;
            }
        }

        return nullptr;
    }
};

#include "main.moc"
