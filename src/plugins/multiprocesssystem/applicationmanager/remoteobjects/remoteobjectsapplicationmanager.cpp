#include "remoteobjectsapplicationmanager.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QProcess>

ApplicationManager::ApplicationManager(QObject *parent)
    : ApplicationManagerSimpleSource(parent)
{}

void ApplicationManager::exec(int id, const QString &key)
{
    if (apps.contains(id)) {
        emit activated(id, key);
    } else {
        auto process = new QProcess(this);
        process->setObjectName(key);
        process->setProgram(QCoreApplication::instance()->applicationFilePath());
        QStringList args {key};
        auto env = QProcess::systemEnvironment();
        env.append("XDG_SESSION_TYPE=wayland");
        env.append("QT_WAYLAND_SHELL_INTEGRATION=ivi-shell");
        env.append(QStringLiteral("QT_IVI_SURFACE_ID=%1").arg(id));
        process->setArguments(args);
        process->setEnvironment(env);
        connect(process, &QProcess::readyReadStandardOutput, this, [this]() {
            auto process = qobject_cast<QProcess *>(sender());
            auto message = process->readAllStandardOutput();
            if (message.endsWith('\n'))
                message.chop(1);
            if (message.isEmpty())
                return;
            qDebug().noquote() << process->objectName() << message;
        });
        connect(process, &QProcess::readyReadStandardError, this, [this]() {
            auto process = qobject_cast<QProcess *>(sender());
            auto message = process->readAllStandardError();
            if (message.endsWith('\n'))
                message.chop(1);
            if (message.isEmpty())
                return;
            qWarning().noquote() << process->objectName() << message;
        });
        process->start();
        connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), process, &QProcess::deleteLater);
        connect(process, &QProcess::destroyed, process, &QProcess::terminate);
        connect(process, &QProcess::destroyed, [this, id]() { apps.remove(id); });
        if (process->waitForStarted()) {
            apps.insert(id, process);
            emit activated(id, key);
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
    connect(&source, &ApplicationManager::currentChanged, this, &RemoteObjectsApplicationManagerServer::currentChanged);
    connect(&source, &ApplicationManager::activated, this, [this](int id) {
        const auto app = findByID(id);
        if (app.isValid())
            emit activated(app);
    });
}

QMpsApplication RemoteObjectsApplicationManagerServer::current() const
{
    return source.current();
}

void RemoteObjectsApplicationManagerServer::setCurrent(const QMpsApplication &current)
{
    source.setCurrent(current);
}

void RemoteObjectsApplicationManagerServer::exec(const QMpsApplication &application)
{
    source.exec(application.id(), application.key());
}

RemoteObjectsApplicationManagerClient::RemoteObjectsApplicationManagerClient(const QString &prefix, QObject *parent)
    : QMpsApplicationManager(prefix, parent)
{
    auto node = new QRemoteObjectNode(this);
    node->connectToNode(QUrl(QStringLiteral("local:app")));
    replica.setNode(node);
    connect(&replica, &ApplicationManagerReplica::currentChanged, this, &RemoteObjectsApplicationManagerClient::currentChanged);
    connect(&replica, &ApplicationManagerReplica::activated, this, [this](int id) {
        const auto app = findByID(id);
        if (app.isValid())
            emit activated(app);
    });
}

QMpsApplication RemoteObjectsApplicationManagerClient::current() const
{
    return replica.current();
}

void RemoteObjectsApplicationManagerClient::setCurrent(const QMpsApplication &current)
{
    replica.pushCurrent(current);
}

void RemoteObjectsApplicationManagerClient::exec(const QString &key)
{
    auto app = findByKey(key);
    replica.exec(app.id(), app.key());
}
