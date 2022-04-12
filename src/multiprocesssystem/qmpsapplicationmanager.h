#ifndef QMPSAPPLICATIONMANAGER_H
#define QMPSAPPLICATIONMANAGER_H

#include "multiprocesssystem_global.h"
#include <QtCore/QAbstractListModel>
#include <QtCore/QScopedPointer>
#include "qmpsapplication.h"

class MULTIPROCESSSYSTEM_EXPORT QMpsApplicationManager : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QMpsApplication current READ current WRITE setCurrent NOTIFY currentChanged)
public:
    explicit QMpsApplicationManager(const QString &prefix, QObject *parent = nullptr);
    ~QMpsApplicationManager() override;

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual QMpsApplication current() const;

    Q_INVOKABLE QMpsApplication findByID(int id) const;
    Q_INVOKABLE QMpsApplication findByKey(const QString &key) const;

public Q_SLOTS:
    void init();
    virtual void setCurrent(const QMpsApplication &current);
    virtual void exec(const QString &key);

Q_SIGNALS:
    void currentChanged(const QMpsApplication &current);
    void activated(const QMpsApplication &application);

protected:
    virtual void exec(const QMpsApplication &application);

private:
    class Private;
    QScopedPointer<Private> d;
};

#endif // QMPSAPPLICATIONMANAGER_H
