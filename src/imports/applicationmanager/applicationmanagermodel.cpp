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
                if (application.attributes() & excludeAttributes)
                    continue;
                if (includeAttributes == QMpsApplication::None
                    || application.attributes() & includeAttributes)
                    appsForMenu.append(application);
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
    connect(this, &ApplicationManagerModel::applicationManagerChanged, this, [this](QMpsApplicationManager* applicationManager) {
        if (applicationManager) {
            connect(applicationManager, &QMpsApplicationManager::applicationStatusChanged, this, [this](const QMpsApplication &application, const QString &status) {
                for (int i = 0; i < appsForMenu.length(); i++) {
                    if (appsForMenu.at(i) == application) {
                        appsForMenu[i].setStatus(status);
                        auto idx = index(i, 0);
                        emit dataChanged(idx, idx, {roleNames().key("status")});
                        break;
                    }
                }
            });
        }
    });
    connect(this, &ApplicationManagerModel::applicationManagerChanged, this, updateList);
    connect(this, &ApplicationManagerModel::excludeAttributesChanged, this, updateList);
    connect(this, &ApplicationManagerModel::includeAttributesChanged, this, updateList);
    connect(this, &ApplicationManagerModel::filtersChanged, this, updateList);
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
