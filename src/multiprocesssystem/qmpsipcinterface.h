#ifndef QMPSIPCINTERFACE_H
#define QMPSIPCINTERFACE_H

#if defined(QT_DBUS_LIB)
#include <QtMultiProcessSystem/qmpsabstractdbusinterface.h>

QT_BEGIN_NAMESPACE

class MULTIPROCESSSYSTEM_EXPORT QMpsIpcInterface : public QMpsAbstractDBusInterface {
public:
    QMpsIpcInterface(QObject *parent = nullptr, Type type = Client)
        : QMpsAbstractDBusInterface(parent, type) {}
};
#else
#include <QtMultiProcessSystem/qmpsabstractipcinterface.h>

QT_BEGIN_NAMESPACE

class MULTIPROCESSSYSTEM_EXPORT QMpsIpcInterface : public QMpsAbstractIpcInterface {
public:
    QMpsIpcInterface(QObject *parent = nullptr, Type type = Client)
        : QMpsAbstractIpcInterface(parent, type) {}
};
#endif

QT_END_NAMESPACE

#define QMpsIpcInterfaceCall QMpsAbstractIpcInterfaceCall
#define QMpsIpcInterfaceGetter QMpsAbstractIpcInterfaceGetter
#define QMpsIpcInterfaceSetter QMpsAbstractIpcInterfaceSetter

#endif // QMPSIPCINTERFACE_H
