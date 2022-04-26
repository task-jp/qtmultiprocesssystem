#include "applicationmanagermodel.h"

#include <QtMultiProcessSystem/QMpsApplicationManager>

ApplicationManagerModel::ApplicationManagerModel(QObject *parent)
    : QAbstractListModel(parent)
{
    auto updateList = [this] () {
        if (!applicationManager)
            return;
        if (!appsForMenu.isEmpty()) {
            beginRemoveRows(QModelIndex(), 0, appsForMenu.length() - 1);
            appsForMenu.clear();
            endRemoveRows();
        }
        if (filters.isEmpty()) {
            for (const auto &application : applicationManager->applications()) {
                if (!(application.attributes() & QMpsApplication::SystemUI)) {
                    appsForMenu.append(application);
                }
            }
        } else {
            for (const auto &key : filters) {
                appsForMenu.append(applicationManager->findByKey(key));
            }
        }
        if (!appsForMenu.isEmpty()) {
            beginInsertRows(QModelIndex(), 0, appsForMenu.length() - 1);
            endInsertRows();
        }
    };
    connect(this, &ApplicationManagerModel::applicationManagerChanged, updateList);
    connect(this, &ApplicationManagerModel::filtersChanged, updateList);
}

QHash<int, QByteArray> ApplicationManagerModel::roleNames() const
{
    QHash<int, QByteArray> ret;
    const auto mo = &QMpsApplication::staticMetaObject;
    for (int i = 0; i < mo->propertyCount(); i++) {
        const auto mp = mo->property(i);
        ret.insert(Qt::UserRole + i, mp.name());
    }
    return ret;
}

int ApplicationManagerModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return appsForMenu.length();
}

QVariant ApplicationManagerModel::data(const QModelIndex &index, int role) const
{
    QVariant ret;
    if (!index.isValid())
        return ret;
    int row = index.row();
    if (row < 0 || row >= appsForMenu.length())
        return ret;
    const auto app = appsForMenu.at(row);
    const auto mo = &QMpsApplication::staticMetaObject;
    const auto role2name = roleNames();
    for (int i = 0; i < mo->propertyCount(); i++) {
        const auto mp = mo->property(i);
        if (role2name.value(role) == mp.name()) {
            ret = mp.readOnGadget(&app);
            break;
        }
    }
    return ret;
}
