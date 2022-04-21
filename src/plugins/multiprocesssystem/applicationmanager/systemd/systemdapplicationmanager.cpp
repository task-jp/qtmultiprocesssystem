#include "systemdapplicationmanager.h"
#include <iostream>
#include <QtDBus>

class SystemdApplicationManager::Private
{
public:
    Private();
    QDBusInterface manager;
    const QString category;
    QHash<QMpsApplication, QDBusObjectPath> processMap;
};

SystemdApplicationManager::Private::Private()
    : manager("org.freedesktop.systemd1", "/org/freedesktop/systemd1", "org.freedesktop.systemd1.Manager")
    , category(qEnvironmentVariable("QT_MULTIPROCESSSYSTEM_APPLICATION_CATEGORY", "example"))
{}

SystemdApplicationManager::SystemdApplicationManager(QObject *parent, Type type)
    : QMpsApplicationManager(parent, type)
    , d(new Private)
{
    connect(this, &SystemdApplicationManager::doExec, this, [this](const QMpsApplication &application) {
        if (d->processMap.contains(application)) {
            emit activated(application);
        } else {
            QString name = QString("%1_%2.service").arg(d->category).arg(application.key());
            QDBusObjectPath path;
            QDBusReply<QDBusObjectPath> reply;
            reply = d->manager.call("GetUnit", name);
            if (reply.isValid()) {
                path = reply.value();
            } else {
                reply = d->manager.call("LoadUnit", name);
                if (reply.isValid()) {
                    path = reply.value();
                } else {
                    qWarning() << d->category << name << reply.error();
                    return;
                }
            }
            qDebug() << path.path();
            reply = d->manager.call("RestartUnit", name, "replace");
            if (reply.isValid()) {
                path = reply.value();
            } else {
                qWarning() << d->category << name << reply.error();
                return;
            }
            d->processMap.insert(application, path);
            emit activated(application);
        }
    });
}

SystemdApplicationManager::~SystemdApplicationManager() = default;
