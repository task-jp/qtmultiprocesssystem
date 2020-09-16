#include "qmpsapplicationfactory.h"

#include "qmpsapplicationplugin.h"
#include "qmpsapplicationmanager.h"

#include <QtCore/private/qfactoryloader_p.h>

Q_GLOBAL_STATIC_WITH_ARGS(QFactoryLoader, loader,
    (QMpsApplicationFactoryInterface_iid,
     QLatin1String("/multiprocesssystem/application"), Qt::CaseInsensitive))

QList<QJsonObject> QMpsApplicationFactory::apps()
{
    return loader()->metaData();
}

QStringList QMpsApplicationFactory::keys()
{
    QStringList list;

    const auto keyMap = loader()->keyMap();
    const auto cend = keyMap.constEnd();
    for (auto it = keyMap.constBegin(); it != cend; ++it)
        if (!list.contains(it.value()))
            list += it.value();
    return list;
}

QMpsApplication *QMpsApplicationFactory::load(const QString &key, QObject *parent)
{
    return qLoadPlugin<QMpsApplication, QMpsApplicationPlugin>(loader(), key.toLower(), parent);
}
