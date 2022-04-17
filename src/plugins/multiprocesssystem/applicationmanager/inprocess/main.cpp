#include <QtMultiProcessSystem/qmpsapplicationmanagerplugin.h>

#include "inprocessapplicationmanager.h"

class QInProcessApplicationManagerPlugin : public QMpsApplicationManagerPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QMpsApplicationManagerFactoryInterface_iid FILE "inprocess.json")
public:
    QMpsApplicationManager *create(const QString &key, QObject *parent, QMpsAbstractIpcInterface::Type type) override
    {
        if (!key.compare(QLatin1String("inprocess"), Qt::CaseInsensitive)) {
            return new InProcessApplicationManager(parent, type);
        }

        return nullptr;
    }
};

#include "main.moc"
