#include <QtMultiProcessSystem/qmpsapplicationmanagerplugin.h>

#include "inprocessapplicationmanager.h"

class QInProcessApplicationManagerPlugin : public QMpsApplicationManagerPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QMpsApplicationManagerFactoryInterface_iid FILE "inprocess.json")
public:
    QMpsApplicationManager *create(const QString &key, QMpsAbstractManagerFactory::Type type, QObject *parent = nullptr) override
    {
        if (!key.compare(QLatin1String("inprocess"), Qt::CaseInsensitive)) {
            switch (type) {
            case QMpsAbstractManagerFactory::Server:
                return new InProcessApplicationManagerServer(parent);
            case QMpsAbstractManagerFactory::Client:
                return new InProcessApplicationManagerClient(parent);
            default:
                break;
            }
        }

        return nullptr;
    }
};

#include "main.moc"
