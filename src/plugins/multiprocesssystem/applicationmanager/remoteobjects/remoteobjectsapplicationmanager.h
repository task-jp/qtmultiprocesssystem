#ifndef REMOTEOBJECTSAPPLICATIONMANAGER_H
#define REMOTEOBJECTSAPPLICATIONMANAGER_H

#include <QtMultiProcessSystem/QMpsApplicationManager>
#include "rep_applicationmanager_merged.h"

class QProcess;

class ApplicationManager : public ApplicationManagerSimpleSource
{
    Q_OBJECT
public:
    explicit ApplicationManager(QObject *parent = nullptr);

public slots:
    void exec(int id, const QString &key) override;

private:
    QMap<int, QProcess *> apps;
};

class RemoteObjectsApplicationManagerServer : public QMpsApplicationManager
{
    Q_OBJECT
public:
    explicit RemoteObjectsApplicationManagerServer(const QString &prefix, QObject *parent = nullptr);

    QMpsApplication current() const override;

public slots:
    void setCurrent(const QMpsApplication &current) override;

protected:
    void exec(const QMpsApplication &application) override;

private:
    ApplicationManager source;
};

class RemoteObjectsApplicationManagerClient : public QMpsApplicationManager
{
    Q_OBJECT
public:
    explicit RemoteObjectsApplicationManagerClient(const QString &prefix, QObject *parent = nullptr);

    QMpsApplication current() const override;

public slots:
    void setCurrent(const QMpsApplication &current) override;
    void exec(const QString &key) override;

private:
    ApplicationManagerReplica replica;
};

#endif // REMOTEOBJECTSAPPLICATIONMANAGER_H
