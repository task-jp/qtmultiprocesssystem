#include "qmpsabstractdbusinterface.h"
#include <QtCore/QMetaClassInfo>

#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusConnectionInterface>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusMetaType>

class QMpsAbstractDBusInterface::Private
{
public:
    Private(QMpsAbstractDBusInterface *parent);
    bool init();
    bool connectToServer();
    void connectSignals();

private:
    QMpsAbstractDBusInterface *q = nullptr;
    const QMetaObject *mo = nullptr;
    QString service;
    QString path;
    QString interface;
    QDBusConnection connection = QDBusConnection::sessionBus();
};

QMpsAbstractDBusInterface::Private::Private(QMpsAbstractDBusInterface *parent)
    : q(parent)
    , service(QString::fromLatin1("com.github.task-jp.qtmultiprocesssystem"))
{}

bool QMpsAbstractDBusInterface::Private::init()
{
    if (!connection.isConnected()) {
        qWarning() << "Cannot connect to the D-Bus session bus";
        return false;
    }

    mo = q->metaObject();
    for (int i = 0; i < mo->classInfoCount(); i++) {
        const auto classInfo = mo->classInfo(i);
        if (QByteArray("D-Bus Service") == classInfo.name()) {
            service = QString::fromUtf8(classInfo.value());
        }
        if (QByteArray("D-Bus Path") == classInfo.name()) {
            path = QString::fromUtf8(classInfo.value());
        }
        if (i < mo->classInfoOffset())
            continue;

        // interface should be declared in the instanciated class
        if (QByteArray("D-Bus Interface") == classInfo.name()) {
            interface = QString::fromUtf8(classInfo.value());
        }
    }
    if (interface.isNull()) {
        qFatal("D-Bus Interface not found in %s", mo->className());
        return false;
    }

    while (mo->superClass()->className() != q->staticMetaObject.className()) {
        mo = mo->superClass();
    }

    if (path.isNull())
        path = QStringLiteral("/%1").arg(QString::fromLatin1(mo->className()).mid(1 /* assuming Q */));

    switch (q->type()) {
    case Unknown:
        qFatal("Unknown type at %s(%d)", Q_FUNC_INFO, __LINE__);
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
        q->setProxy(q);
        break; }
    case Client:
        if (q->proxy())
            return false;
        if (q->server()) {
            // same process mode
            q->setProxy(q->server());
            connectSignals();
        } else {
            // other process mode
            qDebug() << "Client" << service << path << interface;
            if (!connectToServer())
                return false;
        }
        break;
    }
    return true;
}

bool QMpsAbstractDBusInterface::Private::connectToServer()
{
    auto iface = new QDBusInterface(service, path, interface, connection, q);
    if (iface->isValid()) {
        q->setProxy(iface);
        connectSignals();
        qDebug() << "Connected" << service << path << interface;
        return true;
    } else {
        qWarning() << iface->lastError();
        delete iface;
        QTimer::singleShot(1000, q, [this] {connectToServer();});
        return false;
    }
}

void QMpsAbstractDBusInterface::Private::connectSignals()
{
    for (int i = mo->methodOffset(); i < mo->methodCount(); i++) {
        const auto signal2 = mo->method(i);
        if (signal2.methodType() != QMetaMethod::Signal)
            continue;
        auto findSignal = [this](const QByteArray &methodSignature) {
            const auto mo = q->proxy()->metaObject();
            for (int i = 0; i < mo->methodCount(); i++) {
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
}

QMpsAbstractDBusInterface::QMpsAbstractDBusInterface(QObject *parent, Type type)
    : QMpsAbstractIpcInterface(parent, type)
    , d(new Private(this))
{}

QMpsAbstractDBusInterface::~QMpsAbstractDBusInterface() = default;

bool QMpsAbstractDBusInterface::init()
{
    return proxy() || d->init();
}
