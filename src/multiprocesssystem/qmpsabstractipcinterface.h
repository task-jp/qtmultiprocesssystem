#ifndef QMPSABSTRACTIPCINTERFACE_H
#define QMPSABSTRACTIPCINTERFACE_H

#include "multiprocesssystem_global.h"
#include <QtCore/QObject>
#include "qmpsabstractmanagerfactory.h"

class MULTIPROCESSSYSTEM_EXPORT QMpsAbstractIpcInterface : public QObject, public QMpsAbstractManagerFactory
{
    Q_OBJECT
public:
    explicit QMpsAbstractIpcInterface(QObject *parent = nullptr, Type type = Client);
    ~QMpsAbstractIpcInterface() override;

    Type type() const;
    virtual bool init() = 0;

protected:
    virtual QMpsAbstractIpcInterface *server() const = 0;
    QObject *proxy() const;
    void setProxy(QObject *proxy);
    struct QMpsProtectedOnly {};

private:
    class Private;
    QScopedPointer<Private> d;
};

#define QMpsAbstractIpcInterfaceCall(s, c, ...) \
    [this, __VA_ARGS__]() { \
        switch (type()) { \
        case Unknown: \
            qFatal("Unknown type at %s(%d)", Q_FUNC_INFO, __LINE__); \
            break; \
        case Server: \
            QMetaObject::invokeMethod(this, #s, __VA_ARGS__); \
            break; \
        case Client: \
            if (proxy() || init()) \
                QMetaObject::invokeMethod(proxy(), #c, __VA_ARGS__); \
            break; \
        } \
    }()

#define QMpsAbstractIpcInterfaceGetter(t, v, n) \
    [this]() { \
        t ret = v; \
        switch (type()) { \
        case Unknown: \
            qFatal("Unknown type at %s(%d)", Q_FUNC_INFO, __LINE__); \
            break; \
        case Server: \
            ret = d->n; \
            break; \
        case Client: \
            if (proxy()) \
                ret = proxy()->property(#n).value<t>(); \
            break; \
        } \
        return ret; \
    }()

#define QMpsAbstractIpcInterfaceSetter(n) \
    [this, &n]() { \
        switch (type()) { \
        case Unknown: \
            qFatal("Unknown type at %s(%d)", Q_FUNC_INFO, __LINE__); \
            break; \
        case Server: \
            if (d->n == n) return; \
            d->n = n; \
            emit n##Changed(n); \
            break; \
        case Client: \
            if (proxy() || init()) \
                proxy()->setProperty(#n, QVariant::fromValue(n)); \
            break; \
        } \
    }()

#endif // QMPSABSTRACTIPCINTERFACE_H
