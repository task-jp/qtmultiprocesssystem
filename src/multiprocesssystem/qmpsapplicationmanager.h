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
    Q_PROPERTY(QString currentKey READ currentKey NOTIFY currentKeyChanged FINAL)
public:
    explicit QMpsApplicationManager(QObject *parent = nullptr, Type type = Client);
    ~QMpsApplicationManager() override;

    QList<QMpsApplication> applications() const;
    QMpsApplication current() const;
    QString currentKey() const;

    Q_INVOKABLE QMpsApplication findByKey(const QString &key) const;
    Q_INVOKABLE QString applicationStatus(const QMpsApplication &application) const;
    Q_INVOKABLE QString applicationStatusByKey(const QString &key) const;
    Q_INVOKABLE qint64 applicationProcessID(const QMpsApplication &application) const;
    Q_INVOKABLE qint64 applicationProcessIDByKey(const QString &key) const;

public Q_SLOTS:
    void setApplications(const QList<QMpsApplication> &applications);
    void setCurrent(const QMpsApplication &current);
    void exec(const QMpsApplication &application, const QStringList &arguments = {});
    void kill(const QMpsApplication &application);
    void start();
    void setApplicationStatus(const QMpsApplication &application, const QString &status);
    void setApplicationStatusByKey(const QString &key, const QString &status);
    void setApplicationProcessID(const QMpsApplication &application, qint64 processID);
    void setApplicationProcessIDByKey(const QString &key, qint64 processID);

Q_SIGNALS:
    void applicationsChanged(const QList<QMpsApplication> &applications);
    void currentChanged(const QMpsApplication &current);
    void currentKeyChanged(const QString &currentKey);
    void applicationStatusChanged(const QMpsApplication &application, const QString &status);
    void applicationProcessIDChanged(const QMpsApplication &application, qint64 processID);
    void activated(const QMpsApplication &application, const QStringList &arguments);
    void killed(const QMpsApplication &application);
    void doExec(const QMpsApplication &application, const QStringList &arguments);
    void doKill(const QMpsApplication &application);
    void doSetApplicationStatus(const QMpsApplication &application, const QString &status);
    void doSetApplicationProcessID(const QMpsApplication &application, qint64 processID);


protected:
    QMpsAbstractIpcInterface *server() const override;

private:
    class Private;
    QScopedPointer<Private> d;
};

#endif // QMPSAPPLICATIONMANAGER_H
