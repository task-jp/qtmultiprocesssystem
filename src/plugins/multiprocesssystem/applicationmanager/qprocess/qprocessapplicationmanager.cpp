#include "qprocessapplicationmanager.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QProcess>

class QProcessApplicationManager::Private
{
public:
    QHash<QMpsApplication, QProcess *> processMap;
};


QProcessApplicationManager::QProcessApplicationManager(QObject *parent, Type type)
    : QMpsApplicationManager(parent, type)
    , d(new Private)
{
    connect(this, &QProcessApplicationManager::doExec, this, [this](const QMpsApplication &application) {
        if (d->processMap.contains(application)) {
            emit activated(application);
        } else {
            auto process = new QProcess(this);
            process->setObjectName(application.key());
            process->setProgram(QCoreApplication::instance()->applicationFilePath());
            QStringList args {application.key()};
            auto env = QProcess::systemEnvironment();
            env.append("QT_QPA_PLATFORM=wayland"); // MOVE to the plugin
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
            qDebug() << "starting" << application.key();
            process->start();
            connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), process, &QProcess::deleteLater);
            connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, [this](int exitCode, QProcess::ExitStatus exitStatus) {
                const auto process = qobject_cast<QProcess *>(sender());
                if (exitStatus == QProcess::NormalExit) {
                    qDebug() << process->objectName() << "exited with" << exitCode;
                } else {
                    qWarning() << process->objectName() << "crashed with" << exitCode;
                }
            });
            connect(process, &QProcess::destroyed, process, &QProcess::terminate);
            connect(process, &QProcess::destroyed, [this, application]() { d->processMap.remove(application); });
            if (process->waitForStarted()) {
                d->processMap.insert(application, process);
                emit activated(application);
            } else {
                qWarning() << process->errorString();
            }
        }
    });
}

QProcessApplicationManager::~QProcessApplicationManager() = default;

