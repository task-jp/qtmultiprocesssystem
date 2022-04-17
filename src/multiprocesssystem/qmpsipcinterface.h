#ifndef QMPSIPCINTERFACE_H
#define QMPSIPCINTERFACE_H

#if defined(QT_DBUS_LIB)
#include "qmpsabstractdbusinterface.h"
#define QMpsIpcInterface QMpsAbstractDBusInterface
#else
#include "qmpsabstractipcinterface.h"
#endif

#define QMpsIpcInterfaceCall QMpsAbstractIpcInterfaceCall
#define QMpsIpcInterfaceGetter QMpsAbstractIpcInterfaceGetter
#define QMpsIpcInterfaceSetter QMpsAbstractIpcInterfaceSetter

#endif // QMPSIPCINTERFACE_H
