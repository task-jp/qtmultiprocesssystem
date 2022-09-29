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
    const auto metaDataList = loader()->metaData();
    for (int i = 0; i < metaDataList.length(); i++) {
#if QT_VERSION < QT_VERSION_CHECK(6, 3, 0)
        const auto metaData = metaDataList.at(i).value(QStringLiteral("MetaData")).toObject();
#else
        const auto metaData = metaDataList.at(i).value(QtPluginMetaDataKeys::MetaData).toJsonValue().toObject();
#endif
        const auto keys = metaData.value(QLatin1String("Keys")).toArray();
        for (const auto &key : keys) {
            if (key.toString().startsWith(prefix)) {
                ret.append(QMpsApplication::fromJson(metaData));
                break;
            }
        }
    }
    std::sort(ret.begin(), ret.end(), [](const QMpsApplication &a, const QMpsApplication &b) {
        return a.key() < b.key();
    });
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
