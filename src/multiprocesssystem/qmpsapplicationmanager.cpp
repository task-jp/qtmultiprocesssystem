#include "qmpsapplicationmanager.h"

#include "qmpsapplicationfactory.h"

#include <QtCore/QDebug>
#include <QtCore/QMetaProperty>

class QMpsApplicationManager::Private
{
public:
    QMpsApplication current;
    QList<QMpsApplication> apps;
    QList<QMpsApplication> appsForMenu;
};


QMpsApplicationManager::QMpsApplicationManager(const QString &prefix, QObject *parent)
    : QAbstractListModel(parent)
    , d(new Private)
{
    for (const auto &app : QMpsApplicationFactory::apps(prefix)) {
        d->apps.append(app);
        if (!app.isSystemUI())
            d->appsForMenu.append(app);
    }
}

QMpsApplicationManager::~QMpsApplicationManager() = default;

void QMpsApplicationManager::init()
{
    for (const auto &app : d->apps) {
        if (app.isAutoStart()) {
            exec(app);
        }
    }
}

QMpsApplication QMpsApplicationManager::current() const
{
    return d->current;
}

void QMpsApplicationManager::setCurrent(const QMpsApplication &current)
{
    if (d->current == current) return;
    d->current = current;
    emit currentChanged(current);
}

void QMpsApplicationManager::exec(const QString &key)
{
    exec(findByKey(key));
}

void QMpsApplicationManager::exec(const QMpsApplication &application)
{
    if (application.isValid())
        emit activated(application);
}

QMpsApplication QMpsApplicationManager::findByID(int id) const
{
    QMpsApplication ret;
    for (const auto &app : d->apps) {
        if (app.id() == id) {
            ret = app;
            break;
        }
    }
    return ret;
}

QMpsApplication QMpsApplicationManager::findByKey(const QString &key) const
{
    QMpsApplication ret;
    for (const auto &app : d->apps) {
        if (app.key() == key) {
            ret = app;
            break;
        }
    }
    return ret;
}

QHash<int, QByteArray> QMpsApplicationManager::roleNames() const
{
    return {
        { ID, "id" },
        { Key, "key" },
        { Name, "name" },
        { Icon, "icon" },
    };
}

int QMpsApplicationManager::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return d->appsForMenu.length();
}

QVariant QMpsApplicationManager::data(const QModelIndex &index, int role) const
{
    QVariant ret;
    if (!index.isValid())
        return ret;
    int row = index.row();
    if (row < 0 || row >= d->appsForMenu.length())
        return ret;
    const auto app = d->appsForMenu.at(row);
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
