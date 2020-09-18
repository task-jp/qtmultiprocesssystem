#include <QtMultiProcessSystem/qmpsapplicationplugin.h>
#include <QtMultiProcessSystem/qmpsapplication.h>

class Settings : public QMpsApplicationPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QMpsApplicationFactoryInterface_iid FILE "settings.json")
public:
    QMpsApplication *create(const QString &key, QObject *parent = nullptr) override
    {
        if (!key.compare(QLatin1String("settings"), Qt::CaseInsensitive)) {
            return new QMpsApplication(parent);
        }

        return nullptr;
    }
};

#include "settings.moc"
