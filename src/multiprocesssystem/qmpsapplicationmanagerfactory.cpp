#include "qmpsapplicationmanagerfactory.h"
#include "qmpsapplicationmanagerplugin.h"

#include <QtCore/private/qfactoryloader_p.h>

Q_GLOBAL_STATIC_WITH_ARGS(QFactoryLoader, loader,
    (QMpsApplicationManagerFactoryInterface_iid,
     QLatin1String("/multiprocesssystem/applicationmanager"), Qt::CaseInsensitive))

QStringList QMpsApplicationManagerFactory::keys()
{
    QStringList list;

    const auto keyMap = loader()->keyMap();
    const auto cend = keyMap.constEnd();
    for (auto it = keyMap.constBegin(); it != cend; ++it)
        if (!list.contains(it.value()))
            list += it.value();
    return list;
}

QMpsApplicationManager *QMpsApplicationManagerFactory::create(const QString &key, Type type, QObject *parent)
{
    return qLoadPlugin<QMpsApplicationManager, QMpsApplicationManagerPlugin>(loader(), key.toLower(), type, parent);
}
