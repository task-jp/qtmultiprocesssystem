#ifndef QMPSAPPLICATIONMANAGER_H
#define QMPSAPPLICATIONMANAGER_H

#include "multiprocesssystem_global.h"
#include "qmpsipcinterface.h"
#include "qmpsapplication.h"

class MULTIPROCESSSYSTEM_EXPORT QMpsApplicationManager : public QMpsIpcInterface
{
    Q_OBJECT
    Q_PROPERTY(QList<QMpsApplication> applications READ applications WRITE setApplications NOTIFY applicationsChanged)
    Q_PROPERTY(QMpsApplication current READ current WRITE setCurrent NOTIFY currentChanged)
public:
    explicit QMpsApplicationManager(QObject *parent = nullptr, Type type = Client);
    ~QMpsApplicationManager() override;

    QList<QMpsApplication> applications() const;
    QMpsApplication current() const;

    Q_INVOKABLE QMpsApplication findByID(int id) const;
    Q_INVOKABLE QMpsApplication findByKey(const QString &key) const;

public Q_SLOTS:
    void setApplications(const QList<QMpsApplication> &applications);
    void setCurrent(const QMpsApplication &current);
    void exec(const QMpsApplication &application);
    void start();

Q_SIGNALS:
    void applicationsChanged(const QList<QMpsApplication> &applications);
    void currentChanged(const QMpsApplication &current);
    void activated(const QMpsApplication &application);
    void doExec(const QMpsApplication &application);

protected:
    QMpsAbstractIpcInterface *server() const override;

private:
    class Private;
    QScopedPointer<Private> d;
};

#endif // QMPSAPPLICATIONMANAGER_H
