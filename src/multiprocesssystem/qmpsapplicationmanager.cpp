#include "qmpsapplicationmanager.h"

#include "qmpsapplicationfactory.h"

#include <QDebug>

QMpsApplicationManager::QMpsApplicationManager(const QString &prefix, QObject *parent)
    : QAbstractListModel(parent)
{
    for (const auto &app : QMpsApplicationFactory::apps(prefix)) {
        apps.append(app);
        if (!app.isSystemUI())
            appsForMenu.append(app);
    }
}

void QMpsApplicationManager::init()
{
    for (const auto &app : apps) {
        if (app.isAutoStart()) {
            exec(app.id(), app.key());
        }
    }
}

void QMpsApplicationManager::exec(int id, const QString &key)
{
    qDebug() << id << key;
    emit activated(id, key);
}

QHash<int, QByteArray> QMpsApplicationManager::roleNames() const
{
    return {
        { ID, "id" },
        { Key, "key"},
        { Name, "name"},
        { Icon, "icon"},
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
    auto mo = app.staticMetaObject;
    const auto role2name = roleNames();
    for (int i = 0; i < mo.propertyCount(); i++) {
        auto property = mo.property(i);
        if (role2name.value(role) == property.name()) {
            ret = property.readOnGadget(&app);
            break;
        }
    }
    return ret;
}
