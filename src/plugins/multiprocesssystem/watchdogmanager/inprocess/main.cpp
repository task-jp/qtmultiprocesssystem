#include <QtMultiProcessSystem/qmpswatchdogmanagerplugin.h>

#include "inprocesswatchdogmanager.h"

class QInProcessWatchDogManagerPlugin : public QMpsWatchDogManagerPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QMpsWatchDogManagerFactoryInterface_iid FILE "inprocess.json")
public:
    QMpsWatchDogManager *create(const QString &key, QMpsAbstractManagerFactory::Type type, QObject *parent = nullptr) override
    {
        if (!key.compare(QLatin1String("inprocess"), Qt::CaseInsensitive)) {
            switch (type) {
            case QMpsAbstractManagerFactory::Server:
                return new InProcessWatchDogManagerServer(parent);
            case QMpsAbstractManagerFactory::Client:
                return new InProcessWatchDogManagerClient(parent);
            default:
                break;
            }
        }

        return nullptr;
    }
};

#include "main.moc"
