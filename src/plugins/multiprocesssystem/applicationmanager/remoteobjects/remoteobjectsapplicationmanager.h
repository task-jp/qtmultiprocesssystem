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
    void exec(int id, const QString &name) override;

private:
    QMap<int, QProcess *> apps;
};

class RemoteObjectsApplicationManagerServer : public QMpsApplicationManager
{
    Q_OBJECT
public:
    explicit RemoteObjectsApplicationManagerServer(QObject *parent = nullptr);

public slots:
    void exec(int id, const QString &name) override;

private:
    ApplicationManager source;
};

class RemoteObjectsApplicationManagerClient : public QMpsApplicationManager
{
    Q_OBJECT
public:
    explicit RemoteObjectsApplicationManagerClient(QObject *parent = nullptr);

public slots:
    void exec(int id, const QString &name) override;

private:
    ApplicationManagerReplica replica;
};

#endif // REMOTEOBJECTSAPPLICATIONMANAGER_H
