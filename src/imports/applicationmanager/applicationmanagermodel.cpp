#include "applicationmanagermodel.h"

#include <QtMultiProcessSystem/QMpsApplicationManager>

ApplicationManagerModel::ApplicationManagerModel(QObject *parent)
    : QAbstractListModel(parent)
{
    connect(this, &ApplicationManagerModel::applicationManagerChanged, this, [this](QMpsApplicationManager *applicationManager) {
        for (const auto &application : applicationManager->applications()) {
            if (!application.isSystemUI()) {
                appsForMenu.append(application);
            }
        }
    });
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
