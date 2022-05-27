#include "systemdapplicationmanager.h"
#include <iostream>
#include <QtDBus>

class SystemdApplicationManager::Private
{
public:
    Private();
    QDBusInterface manager;
    const QString category;
    QHash<QMpsApplication, QDBusInterface *> processMap;
};

SystemdApplicationManager::Private::Private()
    : manager("org.freedesktop.systemd1", "/org/freedesktop/systemd1", "org.freedesktop.systemd1.Manager")
    , category(qEnvironmentVariable("QT_MULTIPROCESSSYSTEM_APPLICATION_CATEGORY", "example"))
{}

SystemdApplicationManager::SystemdApplicationManager(QObject *parent, Type type)
    : QMpsApplicationManager(parent, type)
    , d(new Private)
{
    connect(this, &SystemdApplicationManager::doExec, this, [this](const QMpsApplication &application, const QStringList &arguments) {
        if (!application.isValid()) {
            return;
        }
        if (d->processMap.contains(application)) {
            emit activated(application, arguments);
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
            if (!reply.isValid()) {
                qWarning() << d->category << name << reply.error();
                return;
            }

            auto unit = new QDBusInterface("org.freedesktop.systemd1", path.path(), "org.freedesktop.systemd1.Unit");
            qDebug() << unit->isValid();
            d->processMap.insert(application, unit);
#if 0
            const auto mo = unit->metaObject();
            for (int i = mo->propertyOffset(); i < mo->propertyCount(); i++)
                qDebug() << mo->property(i).name();
            for (int i = mo->methodOffset(); i < mo->methodCount(); i++)
                qDebug() << mo->method(i).name();
#endif
            qDebug() << unit->property("LoadState") << unit->property("ActiveState") << unit->property("SubState");
            emit activated(application, arguments);
        }
    });

    connect(this, &SystemdApplicationManager::applicationStatusChanged,
            this, [this](const QMpsApplication &application, const QString &status) {
        if (status == QStringLiteral("destroyed")) {
            if (d->processMap.contains(application)) {
                qDebug() << "remove process" << application.key();
                delete d->processMap.take(application);
            }
        }
    });
}

SystemdApplicationManager::~SystemdApplicationManager() = default;
