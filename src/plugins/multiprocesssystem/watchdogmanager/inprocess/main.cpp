#include <QtMultiProcessSystem/qmpswatchdogmanagerplugin.h>

#include "inprocesswatchdogmanager.h"

class QInProcessWatchDogManagerPlugin : public QMpsWatchDogManagerPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QMpsWatchDogManagerFactoryInterface_iid FILE "inprocess.json")
public:
    QMpsWatchDogManager *create(const QString &key, QObject *parent, QMpsAbstractIpcInterface::Type type) override
    {
        if (!key.compare(QLatin1String("inprocess"), Qt::CaseInsensitive)) {
            return new InProcessWatchDogManager(parent, type);
        }

        return nullptr;
    }
};

#include "main.moc"
