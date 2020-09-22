#ifndef QMPSAPPLICATIONMANAGER_H
#define QMPSAPPLICATIONMANAGER_H

#include "multiprocesssystem_global.h"
#include <QtCore/QAbstractListModel>
#include "qmpsapplication.h"

class MULTIPROCESSSYSTEM_EXPORT QMpsApplicationManager : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit QMpsApplicationManager(const QString &prefix, QObject *parent = nullptr);

    enum Roles {
        ID = Qt::UserRole + 1,
        Key,
        Name,
        Icon,
    };

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public Q_SLOTS:
    void init();
    virtual void exec(int id, const QString &key);

Q_SIGNALS:
    void activated(int id, const QString &key);

private:
    QList<QMpsApplication> apps;
    QList<QMpsApplication> appsForMenu;
};

#endif // QMPSAPPLICATIONMANAGER_H
