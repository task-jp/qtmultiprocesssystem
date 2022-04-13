#include "qmpsapplicationfactory.h"

#include "qmpsapplicationplugin.h"
#include "qmpsapplicationmanager.h"
#include "qmpsapplication.h"

#include <QtCore/QJsonArray>
#include <QtCore/private/qfactoryloader_p.h>

Q_GLOBAL_STATIC_WITH_ARGS(QFactoryLoader, loader,
    (QMpsApplicationFactoryInterface_iid,
     QLatin1String("/multiprocesssystem/application"), Qt::CaseInsensitive))

QList<QMpsApplication> QMpsApplicationFactory::apps(const QString &prefix)
{
    QList<QMpsApplication> ret;
    for (const auto &app : loader()->metaData()) {
        const auto metaData = app.value(QLatin1String("MetaData")).toObject();
        const auto keys = metaData.value(QLatin1String("Keys"));
        for (const auto &key : keys.toArray()) {
            if (key.toString().startsWith(prefix)) {
                ret.append(QMpsApplication::fromJson(metaData));
                break;
            }
        }
    }
    return ret;
}

QStringList QMpsApplicationFactory::keys()
{
    return loader()->keyMap().values();
}

QObject *QMpsApplicationFactory::load(const QString &key, QObject *parent)
{
    return qLoadPlugin<QObject, QMpsApplicationPlugin>(loader(), key.toLower(), parent);
}
