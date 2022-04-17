#include <QtMultiProcessSystem/qmpswindowmanagerplugin.h>
#include <QtMultiProcessSystem/qmpswindowmanager.h>

class QWaylandWindowManagerPlugin : public QMpsWindowManagerPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QMpsWindowManagerFactoryInterface_iid FILE "wayland.json")
public:
    QMpsWindowManager *create(const QString &key, QMpsAbstractManagerFactory::Type type, QObject *parent = nullptr) override
    {
        if (key.compare(QLatin1String("wayland"), Qt::CaseInsensitive))
            return nullptr;

        if (qEnvironmentVariableIsEmpty("QT_WAYLAND_DISABLE_WINDOWDECORATION"))
            qputenv("QT_WAYLAND_DISABLE_WINDOWDECORATION", "1");
        qputenv("QT_QPA_PLATFORM", "wayland");

        return new QMpsWindowManager(parent);
    }
};

#include "main.moc"
