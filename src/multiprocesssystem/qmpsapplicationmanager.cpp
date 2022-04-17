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
    connect(this, &QMpsApplicationManager::doExec, this, [](const QMpsApplication &application) {
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

#if 0
QHash<int, QByteArray> QMpsApplicationManager::roleNames() const
{
    QHash<int, QByteArray> ret;
    const auto mo = &QMpsApplication::staticMetaObject;
    for (int i = 0; i < mo->propertyCount(); i++) {
        const auto mp = mo->property(i);
        ret.insert(Qt::UserRole + i, mp.name());
    }
    return ret;
}

int QMpsApplicationManager::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return d->appsForMenu.length();
}

QVariant QMpsApplicationManager::data(const QModelIndex &index, int role) const
{
    QVariant ret;
    if (!index.isValid())
        return ret;
    int row = index.row();
    if (row < 0 || row >= d->appsForMenu.length())
        return ret;
    const auto app = d->appsForMenu.at(row);
    const auto mo = &QMpsApplication::staticMetaObject;
    const auto role2name = roleNames();
    for (int i = 0; i < mo->propertyCount(); i++) {
        const auto mp = mo->property(i);
        if (role2name.value(role) == mp.name()) {
            ret = mp.readOnGadget(&app);
            break;
        }
    }
    return ret;
}
#endif
