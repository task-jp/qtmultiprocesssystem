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
    , d(type == Server ? new Private : nullptr)
{
#if defined(QT_DBUS_LIB)
    qDBusRegisterMetaType<QMpsApplication>();
    qDBusRegisterMetaType<QList<QMpsApplication>>();
#endif

    switch (type) {
    case Unknown:
        qFatal("Unknown type at %s(%d)", Q_FUNC_INFO, __LINE__);
        break;
    case Server:
        Private::server = this;
        break;
    case Client:
        break;
    }

    if (type == Server) {
        connect(this, &QMpsApplicationManager::doSetApplicationStatus,
                this, [this](const QMpsApplication &application, const QString &status) {
            if (!d->applications.contains(application)) return;
            int index = d->applications.indexOf(application);
            QMpsApplication &app = d->applications[index];
            if (app.status() == status) return;
            qDebug() << "Status" << app.key() << app.status() << "==>" << status;
            app.setStatus(status);
            emit applicationStatusChanged(app, status);
        });
        connect(this, &QMpsApplicationManager::doSetApplicationProcessID,
                this, [this](const QMpsApplication &application, qint64 processID) {
            if (!d->applications.contains(application)) return;
            int index = d->applications.indexOf(application);
            QMpsApplication &app = d->applications[index];
            if (app.processID() == processID) return;
            qDebug() << "ProcessID" << app.key() << app.processID() << "==>" << processID;
            app.setProcessID(processID);
            emit applicationProcessIDChanged(app, processID);
        });
    }
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

QString QMpsApplicationManager::applicationStatus(const QMpsApplication &application) const
{
    QString ret;
    switch (type()) {
    case Unknown:
        qFatal("Unknown type at %s(%d)", Q_FUNC_INFO, __LINE__);
        break;
    case Server:
        for (const auto &app : applications()) {
            if (app.key() == application.key()) {
                ret = app.status();
                break;
            }
        }
        break;
    case Client:
        if (proxy())
            QMetaObject::invokeMethod(proxy(), "applicationStatus", Q_RETURN_ARG(QString, ret), Q_ARG(QMpsApplication, application));
        break;
    }
    return ret;
}

QString QMpsApplicationManager::applicationStatusByKey(const QString &key) const
{
    return applicationStatus(findByKey(key));
}

qint64 QMpsApplicationManager::applicationProcessID(const QMpsApplication &application) const
{
    qint64 ret = -1;
    switch (type()) {
    case Unknown:
        qFatal("Unknown type at %s(%d)", Q_FUNC_INFO, __LINE__);
        break;
    case Server:
        for (const auto &app : applications()) {
            if (app.key() == application.key()) {
                ret = app.processID();
                break;
            }
        }
        break;
    case Client:
        if (proxy())
            QMetaObject::invokeMethod(proxy(), "applicationProcessID", Q_RETURN_ARG(qint64, ret), Q_ARG(QMpsApplication, application));
        break;
    }
    return ret;
}

qint64 QMpsApplicationManager::applicationProcessIDByKey(const QString &key) const
{
    return applicationProcessID(findByKey(key));
}

void QMpsApplicationManager::setApplicationStatus(const QMpsApplication &application, const QString &status)
{
    const auto arg1 = Q_ARG(QMpsApplication, application);
    const auto arg2 = Q_ARG(QString, status);
    QMpsAbstractIpcInterfaceCall(doSetApplicationStatus, setApplicationStatus, arg1, arg2);
}

void QMpsApplicationManager::setApplicationStatusByKey(const QString &key, const QString &status)
{
    setApplicationStatus(findByKey(key), status);
}

void QMpsApplicationManager::setApplicationProcessID(const QMpsApplication &application, qint64 processID)
{
    const auto arg1 = Q_ARG(QMpsApplication, application);
    const auto arg2 = Q_ARG(qint64, processID);
    QMpsAbstractIpcInterfaceCall(doSetApplicationProcessID, setApplicationProcessID, arg1, arg2);
}

void QMpsApplicationManager::setApplicationProcessIDByKey(const QString &key, qint64 processID)
{
    setApplicationProcessID(findByKey(key), processID);
}

void QMpsApplicationManager::exec(const QMpsApplication &application, const QStringList &arguments)
{
    const auto arg1 = Q_ARG(QMpsApplication, application);
    const auto arg2 = Q_ARG(QStringList, arguments);
    QMpsAbstractIpcInterfaceCall(doExec, exec, arg1, arg2);
}

void QMpsApplicationManager::kill(const QMpsApplication &application)
{
    const auto arg1 = Q_ARG(QMpsApplication, application);
    QMpsAbstractIpcInterfaceCall(doKill, kill, arg1);
}

void QMpsApplicationManager::start()
{
    for (const auto &app : applications()) {
        if (app.attributes() & QMpsApplication::AutoStart) {
            exec(app);
        }
    }
}

QMpsAbstractIpcInterface *QMpsApplicationManager::server() const
{
    return Private::server;
}
