#include "remoteobjectsapplicationmanager.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QProcess>

ApplicationManager::ApplicationManager(QObject *parent)
    : ApplicationManagerSimpleSource(parent)
{}

void ApplicationManager::exec(int id, const QString &name)
{
    if (apps.contains(id)) {
        emit activated(id, name);
    } else {
        auto process = new QProcess(this);
        process->setProgram(QCoreApplication::instance()->applicationFilePath());
        QStringList args {name};
        auto env = QProcess::systemEnvironment();
        env.append("XDG_SESSION_TYPE=wayland");
        env.append("QT_WAYLAND_SHELL_INTEGRATION=ivi-shell");
        env.append(QStringLiteral("QT_IVI_SURFACE_ID=%1").arg(id));
        process->setArguments(args);
        process->setEnvironment(env);
        connect(process, &QProcess::readyReadStandardOutput, [process]() {
            qDebug() << process->readAllStandardOutput();
        });
        connect(process, &QProcess::readyReadStandardError, [process]() {
            qWarning() << process->readAllStandardError();
        });
        process->start();
        connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), process, &QProcess::deleteLater);
        connect(process, &QProcess::destroyed, process, &QProcess::terminate);
        connect(process, &QProcess::destroyed, [this, id]() { apps.remove(id); });
        if (process->waitForStarted()) {
            apps.insert(id, process);
            emit activated(id, name);
        } else {
            qWarning() << process->errorString();
        }
    }
}

RemoteObjectsApplicationManagerServer::RemoteObjectsApplicationManagerServer(const QString &prefix, QObject *parent)
    : QMpsApplicationManager(prefix, parent)
{
    auto host = new QRemoteObjectHost(QUrl(QStringLiteral("local:app")), this);
    host->enableRemoting(&source);
    connect(&source, &ApplicationManager::activated, this, &RemoteObjectsApplicationManagerServer::activated);
}


void RemoteObjectsApplicationManagerServer::exec(int id, const QString &name)
{
    source.exec(id, name);
}

RemoteObjectsApplicationManagerClient::RemoteObjectsApplicationManagerClient(const QString &prefix, QObject *parent)
    : QMpsApplicationManager(prefix, parent)
{
    auto node = new QRemoteObjectNode(this);
    node->connectToNode(QUrl(QStringLiteral("local:app")));
    replica.setNode(node);
    connect(&replica, &ApplicationManagerReplica::activated, this, &RemoteObjectsApplicationManagerClient::activated);
}

void RemoteObjectsApplicationManagerClient::exec(int id, const QString &name)
{
    replica.exec(id, name);
}
