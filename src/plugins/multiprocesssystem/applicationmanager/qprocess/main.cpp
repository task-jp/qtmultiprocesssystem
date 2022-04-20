#include <QtMultiProcessSystem/qmpsapplicationmanagerplugin.h>

#include "qprocessapplicationmanager.h"

class QProcessApplicationManagerPlugin : public QMpsApplicationManagerPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QMpsApplicationManagerFactoryInterface_iid FILE "qprocess.json")
public:
    QMpsApplicationManager *create(const QString &key, QObject *parent, QMpsAbstractIpcInterface::Type type) override
    {
        if (!key.compare(QLatin1String("qprocess"), Qt::CaseInsensitive)) {
            return new QProcessApplicationManager(parent, type);
        }

        return nullptr;
    }
};

#include "main.moc"
