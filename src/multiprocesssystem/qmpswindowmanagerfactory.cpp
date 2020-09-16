#include "qmpswindowmanagerfactory.h"
#include "qmpswindowmanagerplugin.h"

#include <QtCore/private/qfactoryloader_p.h>

Q_GLOBAL_STATIC_WITH_ARGS(QFactoryLoader, loader,
    (QMpsWindowManagerFactoryInterface_iid,
     QLatin1String("/multiprocesssystem/windowmanager"), Qt::CaseInsensitive))

QStringList QMpsWindowManagerFactory::keys()
{
    QStringList list;

    const auto keyMap = loader()->keyMap();
    const auto cend = keyMap.constEnd();
    for (auto it = keyMap.constBegin(); it != cend; ++it)
        if (!list.contains(it.value()))
            list += it.value();
    return list;
}

QMpsWindowManager *QMpsWindowManagerFactory::create(const QString &key, Type type, QObject *parent)
{
    return qLoadPlugin<QMpsWindowManager, QMpsWindowManagerPlugin>(loader(), key.toLower(), type, parent);
}
