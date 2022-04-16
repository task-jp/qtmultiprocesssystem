#include "qmpsabstractdbusinterface.h"
#include <QtCore/QMetaClassInfo>

#include <QtCore/QDebug>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusConnectionInterface>
#include <QtDBus/QDBusInterface>

class QMpsAbstractDBusInterface::Private
{
public:
    Private(QMpsAbstractDBusInterface *parent);
    bool init();

private:
    QMpsAbstractDBusInterface *q = nullptr;
    const QMetaObject *mo = nullptr;
    const QString service;
    QString path;
    QString interface;
};

QMpsAbstractDBusInterface::Private::Private(QMpsAbstractDBusInterface *parent)
    : q(parent)
    , service(QString::fromLatin1("com.github.task-jp.qtmultiprocesssystem"))
{
}

bool QMpsAbstractDBusInterface::Private::init()
{
    QDBusConnection connection = QDBusConnection::sessionBus();
    if (!connection.isConnected()) {
        qWarning() << "Cannot connect to the D-Bus session bus";
        return false;
    }

    mo = q->metaObject();
    while (mo->superClass()->className() != q->staticMetaObject.className()) {
        mo = mo->superClass();
    }
    path = QStringLiteral("/%1").arg(QString::fromLatin1(mo->className()).mid(1 /* Q */));
    for (int i = 0; i < mo->classInfoCount(); i++) {
        const auto classInfo = mo->classInfo(i);
        if (QByteArray("D-Bus Interface") == classInfo.name()) {
            interface = QString::fromUtf8(classInfo.value());
        }
    }

    if (interface.isNull()) {
        qWarning() << "D-Bus Interface not found";
        return false;
    }

    switch (q->type()) {
    case Unknown:
        qWarning() << "Cannot init object with type=Unknown";
        return false;
        break;
    case Server: {
        const auto registeredServiceNames = connection.interface()->registeredServiceNames();
        if (!registeredServiceNames.isValid()) {
            qWarning() << registeredServiceNames.error();
            return false;
        }
        if (!registeredServiceNames.value().contains(service)) {
            if (!connection.registerService(service)) {
                qWarning() << "registerService failure" << service;
                return false;
            }
        }

        qDebug() << "Server" << service << path << interface;
        if (!connection.registerObject(path, interface, q, QDBusConnection::ExportAllContents)) {
            qWarning() << "registering" << mo->className() << "failed";
            return false;
        }
        break; }
    case Client:
        if (q->proxy())
            return false;
        if (q->server()) {
            // same process mode
            q->setProxy(q->server());
        } else {
            // other process mode
            qDebug() << "Client" << service << path << interface;
            auto iface = new QDBusInterface(service, path, interface, connection, q);
            if (iface->isValid()) {
                q->setProxy(iface);
            } else {
                qWarning() << iface->lastError();
                delete iface;
                return false;
            }
        }

        for (int i = mo->methodOffset(); i < mo->methodCount(); i++) {
            const auto signal2 = mo->method(i);
            if (signal2.methodType() != QMetaMethod::Signal)
                continue;
            auto findSignal = [this](const QByteArray &methodSignature) {
//                qDebug() << methodSignature;
                const auto mo = q->proxy()->metaObject();
                for (int i = mo->methodOffset(); i < mo->methodCount(); i++) {
                    const auto mm = mo->method(i);
                    if (mm.methodType() != QMetaMethod::Signal)
                        continue;
                    if (mm.methodSignature() == methodSignature)
                        return mm;
                }
                qWarning() << methodSignature << "not found in" << q->proxy();
                return QMetaMethod();
            };
            const auto signal1 = findSignal(signal2.methodSignature());
            if (signal1.isValid()) {
                connect(q->proxy(), signal1, q, signal2, Qt::UniqueConnection);
            }
        }
        break;
    }
    return true;
}

QMpsAbstractDBusInterface::QMpsAbstractDBusInterface(QObject *parent, Type type)
    : QMpsAbstractIpcInterface(parent, type)
    , d(new Private(this))
{}

QMpsAbstractDBusInterface::~QMpsAbstractDBusInterface() = default;

bool QMpsAbstractDBusInterface::init()
{
    return d->init();
}
