#ifndef QMPSAPPLICATIONMANAGER_H
#define QMPSAPPLICATIONMANAGER_H

#include "multiprocesssystem_global.h"
#include <QtCore/QAbstractListModel>
#include <QtCore/QJsonObject>

class MULTIPROCESSSYSTEM_EXPORT QMpsApplicationManager : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit QMpsApplicationManager(QObject *parent = nullptr);

    enum Roles {
        ID = Qt::UserRole + 1,
        Name,
        Icon,
        Title,
    };

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public slots:
    void init();
    virtual void exec(int id, const QString &name);

signals:
    void activated(int id, const QString &name);

private:
    QList<QJsonObject> apps;
    QList<QJsonObject> appsForMenu;
};

#endif // QMPSAPPLICATIONMANAGER_H
