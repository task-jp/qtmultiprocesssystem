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

QMpsApplicationManager *QMpsApplicationManagerFactory::create(const QString &key, QObject *parent, QMpsAbstractManagerFactory::Type type)
{
    auto *ret = qLoadPlugin<QMpsApplicationManager, QMpsApplicationManagerPlugin>(loader(), key.toLower(), parent, type);
    if (!ret)
        qFatal("Application manager %s not found\navaialble managers: %s", qPrintable(key), qPrintable(keys().join(QStringLiteral(", "))));
    qputenv("QT_MULTIPROCESSSYSTEM_APPLICATIONMANAGER", key.toUtf8());
    return ret;
}
