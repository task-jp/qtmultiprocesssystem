#include "renderthreadwatchdog.h"
#include <QtMultiProcessSystem/QMpsWatchDog>

class RenderThreadWatchDog::Private
{
public:
    QMpsWatchDog watchDog = QMpsWatchDog("render-thread");
    QMpsApplication application;
};

RenderThreadWatchDog::RenderThreadWatchDog(QQuickItem *parent)
    : QQuickItem(parent)
    , d(new Private)
{
    setFlag(ItemHasContents);
}

RenderThreadWatchDog::~RenderThreadWatchDog() = default;

QMpsApplication RenderThreadWatchDog::application() const
{
    return d->application;
}

void RenderThreadWatchDog::setApplication(const QMpsApplication &application)
{
    if (d->application == application) return;
    d->application = application;
    emit applicationChanged(application);
}

void RenderThreadWatchDog::pang()
{
    update();
}

void RenderThreadWatchDog::pangInternal()
{
    d->watchDog.pang(d->application);
}

QSGNode *RenderThreadWatchDog::updatePaintNode(QSGNode *node, UpdatePaintNodeData *)
{
    QMetaObject::invokeMethod(this, "pangInternal", Qt::QueuedConnection);
    return node;
}
