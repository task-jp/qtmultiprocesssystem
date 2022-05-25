#ifndef QMPSAPPLICATIONMANAGER_H
#define QMPSAPPLICATIONMANAGER_H

#include "multiprocesssystem_global.h"
#include "qmpsipcinterface.h"
#include "qmpsapplication.h"

class MULTIPROCESSSYSTEM_EXPORT QMpsApplicationManager : public QMpsIpcInterface
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "local.ApplicationManager")
    Q_PROPERTY(QList<QMpsApplication> applications READ applications WRITE setApplications NOTIFY applicationsChanged)
    Q_PROPERTY(QMpsApplication current READ current WRITE setCurrent NOTIFY currentChanged)
public:
    explicit QMpsApplicationManager(QObject *parent = nullptr, Type type = Client);
    ~QMpsApplicationManager() override;

    QList<QMpsApplication> applications() const;
    QMpsApplication current() const;

    Q_INVOKABLE QMpsApplication findByKey(const QString &key) const;
    Q_INVOKABLE QString applicationStatus(const QMpsApplication &application) const;
    Q_INVOKABLE QString applicationStatusByKey(const QString &key) const;

public Q_SLOTS:
    void setApplications(const QList<QMpsApplication> &applications);
    void setCurrent(const QMpsApplication &current);
    void exec(const QMpsApplication &application, const QStringList &arguments = {});
    void kill(const QMpsApplication &application);
    void start();
    void setApplicationStatus(const QMpsApplication &application, const QString &status);
    void setApplicationStatusByKey(const QString &key, const QString &status);

Q_SIGNALS:
    void applicationsChanged(const QList<QMpsApplication> &applications);
    void currentChanged(const QMpsApplication &current);
    void applicationStatusChanged(const QMpsApplication &application, const QString &status);
    void activated(const QMpsApplication &application, const QStringList &arguments);
    void killed(const QMpsApplication &application);
    void doExec(const QMpsApplication &application, const QStringList &arguments);
    void doKill(const QMpsApplication &application);
    void doSetApplicationStatus(const QMpsApplication &application, const QString &status);

protected:
    QMpsAbstractIpcInterface *server() const override;

private:
    class Private;
    QScopedPointer<Private> d;
};

#endif // QMPSAPPLICATIONMANAGER_H
