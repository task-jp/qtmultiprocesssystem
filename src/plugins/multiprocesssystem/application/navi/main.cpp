#include <QtMultiProcessSystem/qmpsapplicationplugin.h>
#include <QtMultiProcessSystem/qmpsapplication.h>

class Navi : public QMpsApplicationPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QMpsApplicationFactoryInterface_iid FILE "main.json")
public:
    QMpsApplication *create(const QString &key, QObject *parent = nullptr) override
    {
        if (!key.compare(QLatin1String("navi"), Qt::CaseInsensitive)) {
            return new QMpsApplication(parent);
        }

        return nullptr;
    }
};

#include "main.moc"
