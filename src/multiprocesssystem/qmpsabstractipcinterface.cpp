#include "qmpsabstractipcinterface.h"

class QMpsAbstractIpcInterface::Private
{
public:
    Private(QMpsAbstractIpcInterface *parent, Type type);
    bool init();

private:
    QMpsAbstractIpcInterface *q = nullptr;

public:
    Type type;
    QObject *proxy = nullptr;
};

QMpsAbstractIpcInterface::Private::Private(QMpsAbstractIpcInterface *parent, QMpsAbstractIpcInterface::Type type)
    : q(parent)
    , type(type)
{
}

QMpsAbstractIpcInterface::QMpsAbstractIpcInterface(QObject *parent, QMpsAbstractIpcInterface::Type type)
    : QObject(parent)
    , d(new Private(this, type))
{}

QMpsAbstractIpcInterface::~QMpsAbstractIpcInterface() = default;

QMpsAbstractIpcInterface::Type QMpsAbstractIpcInterface::type() const
{
//    return d ? d->type : Unknown;
    return d->type;
}

QObject *QMpsAbstractIpcInterface::proxy() const
{
//    return d ? d->proxy : nullptr;
    return d->proxy;
}

void QMpsAbstractIpcInterface::setProxy(QObject *proxy)
{
    d->proxy = proxy;
}
