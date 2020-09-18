#include <QtMultiProcessSystem/qmpsapplicationplugin.h>
#include <QtMultiProcessSystem/qmpsapplication.h>

class Weather : public QMpsApplicationPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QMpsApplicationFactoryInterface_iid FILE "weather.json")
public:
    QMpsApplication *create(const QString &key, QObject *parent = nullptr) override
    {
        if (!key.compare(QLatin1String("weather"), Qt::CaseInsensitive)) {
            return new QMpsApplication(parent);
        }

        return nullptr;
    }
};

#include "weather.moc"
