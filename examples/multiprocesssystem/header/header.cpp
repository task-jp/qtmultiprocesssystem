#include <QtMultiProcessSystem/qmpsapplicationplugin.h>
#include <QtMultiProcessSystem/qmpsapplication.h>

class Header : public QMpsApplicationPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QMpsApplicationFactoryInterface_iid FILE "header.json")
public:
    QMpsApplication *create(const QString &key, QObject *parent = nullptr) override
    {
        if (!key.compare(QLatin1String("header"), Qt::CaseInsensitive)) {
            return new QMpsApplication(parent);
        }

        return nullptr;
    }
};

#include "header.moc"
