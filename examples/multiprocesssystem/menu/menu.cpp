#include <QtMultiProcessSystem/qmpsapplicationplugin.h>
#include <QtMultiProcessSystem/qmpsapplication.h>

class Menu : public QMpsApplicationPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QMpsApplicationFactoryInterface_iid FILE "menu.json")
public:
    QMpsApplication *create(const QString &key, QObject *parent = nullptr) override
    {
        if (!key.compare(QLatin1String("menu"), Qt::CaseInsensitive)) {
            return new QMpsApplication(parent);
        }

        return nullptr;
    }
};

#include "menu.moc"
