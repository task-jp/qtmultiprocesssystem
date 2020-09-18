#include "qmpsapplicationmanager.h"

#include "qmpsapplicationfactory.h"

#include <QDebug>

QMpsApplicationManager::QMpsApplicationManager(const QString &prefix, QObject *parent)
    : QAbstractListModel(parent)
{
    for (const auto &app: QMpsApplicationFactory::apps()) {
        const auto metaData = app.value(QLatin1String("MetaData")).toObject();
        const auto keys = metaData.value(QLatin1String("Keys")).toArray();
        for (const auto &key : keys) {
            if (key.toString().startsWith(prefix)) {
                apps.append(metaData);
                if (metaData.value(QLatin1String("ShowInMenu")).toBool())
                    appsForMenu.append(metaData);
                break;
            }
        }
    }
}

void QMpsApplicationManager::init()
{
    for (const auto &app : apps) {
        const auto id = app.value(QLatin1String("ID")).toInt();
        const auto name = app.value(QLatin1String("Name")).toString();
        if (app.value(QLatin1String("LaunchAtBoot")).toBool()) {
            exec(id, name);
        }
    }
}

void QMpsApplicationManager::exec(int id, const QString &name)
{
    emit activated(id, name);
}

QHash<int, QByteArray> QMpsApplicationManager::roleNames() const
{
    return {
        { ID, "id" },
        { Name, "name"},
        { Icon, "icon"},
        { Title, "title"},
    };
}

int QMpsApplicationManager::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return appsForMenu.length();
}

QVariant QMpsApplicationManager::data(const QModelIndex &index, int role) const
{
    QVariant ret;
    if (!index.isValid())
        return ret;
    int row = index.row();
    if (row < 0 || row >= appsForMenu.length())
        return ret;
    const auto app = appsForMenu.at(row);
    switch (role) {
    case ID:
        ret = app.value(QLatin1String("ID")).toInt();
        break;
    case Name:
        ret = app.value(QLatin1String("Name")).toString();
        break;
    case Icon:
        ret = app.value(QLatin1String("Icon")).toString();
        break;
    case Title:
        ret = app.value(QLatin1String("Title")).toString();
        break;
    }

    return ret;
}
