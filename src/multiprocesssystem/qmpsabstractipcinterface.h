#ifndef QMPSABSTRACTIPCINTERFACE_H
#define QMPSABSTRACTIPCINTERFACE_H

#include "multiprocesssystem_global.h"
#include <QtCore/QObject>

class MULTIPROCESSSYSTEM_EXPORT QMpsAbstractIpcInterface : public QObject
{
    Q_OBJECT
public:
    enum Type {
        Unknown,
        Server,
        Client,
    };
    explicit QMpsAbstractIpcInterface(QObject *parent = nullptr, Type type = Client);
    ~QMpsAbstractIpcInterface() override;

    Type type() const;
    virtual bool init() = 0;

protected:
    virtual QMpsAbstractIpcInterface *server() const = 0;
    QObject *proxy() const;
    void setProxy(QObject *proxy);

private:
    class Private;
    QScopedPointer<Private> d;
};

#define QMpsAbstractIpcInterfaceGetter(t, v, n) \
    t ret = v; \
    switch (type()) { \
    case Unknown: \
        break; \
    case Server: \
        ret = d->n; \
        break; \
    case Client: \
        ret = proxy()->property(#n).value<t>(); \
        break; \
    } \
    return ret;

#define QMpsAbstractIpcInterfaceSetter(n) \
    switch (type()) { \
    case Unknown: \
        break; \
    case Server: \
        if (d->n == n) return; \
        d->n = n; \
        emit n##Changed(n); \
        break; \
    case Client: \
        proxy()->setProperty(#n, n); \
        break; \
    }

#endif // QMPSABSTRACTIPCINTERFACE_H
