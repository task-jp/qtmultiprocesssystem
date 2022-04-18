#include "qmpsapplicationmanager.h"

#include "qmpsapplicationfactory.h"

#include <QtCore/QDebug>
#include <QtCore/QMetaProperty>

#if defined(QT_DBUS_LIB)
#include <QtDBus/QDBusMetaType>
#endif

class QMpsApplicationManager::Private
{
public:
    QList<QMpsApplication> applications;
    QMpsApplication current;
    static QMpsApplicationManager *server;
};

QMpsApplicationManager *QMpsApplicationManager::Private::server = nullptr;

QMpsApplicationManager::QMpsApplicationManager(QObject *parent, Type type)
    : QMpsIpcInterface(parent, type)
    , d(new Private)
{
#if defined(QT_DBUS_LIB)
    qDBusRegisterMetaType<QMpsApplication>();
    qDBusRegisterMetaType<QList<QMpsApplication>>();
#endif

    switch (type) {
    case Server:
        Private::server = this;
        break;
    case Client:
        break;
    }
    connect(this, &QMpsApplicationManager::currentChanged, this, [](const QMpsApplication &application) {
        qDebug() << application.key();
    });
}

QMpsApplicationManager::~QMpsApplicationManager() = default;

QList<QMpsApplication> QMpsApplicationManager::applications() const
{
    return QMpsIpcInterfaceGetter(QList<QMpsApplication>, QList<QMpsApplication>(), applications);
}

void QMpsApplicationManager::setApplications(const QList<QMpsApplication> &applications)
{
    QMpsIpcInterfaceSetter(applications);
}

QMpsApplication QMpsApplicationManager::current() const
{
    return QMpsIpcInterfaceGetter(QMpsApplication, QMpsApplication(), current);
}

void QMpsApplicationManager::setCurrent(const QMpsApplication &current)
{
    qDebug() << current.key();
    QMpsIpcInterfaceSetter(current);
}

QMpsApplication QMpsApplicationManager::findByID(int id) const
{
    QMpsApplication ret;
    for (const auto &app : applications()) {
        if (app.id() == id) {
            ret = app;
            break;
        }
    }
    return ret;
}

QMpsApplication QMpsApplicationManager::findByKey(const QString &key) const
{
    QMpsApplication ret;
    for (const auto &app : applications()) {
        if (app.key() == key) {
            ret = app;
            break;
        }
    }
    return ret;
}

void QMpsApplicationManager::exec(const QMpsApplication &application)
{
    auto arg1 = Q_ARG(QMpsApplication, application);
    QMpsAbstractIpcInterfaceCall(doExec, exec, arg1);
}

void QMpsApplicationManager::start()
{
    for (const auto &app : applications()) {
        if (app.isAutoStart()) {
            exec(app);
        }
    }
}

QMpsAbstractIpcInterface *QMpsApplicationManager::server() const
{
    return Private::server;
}
