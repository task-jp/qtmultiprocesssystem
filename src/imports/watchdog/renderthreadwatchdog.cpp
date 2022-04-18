#include "renderthreadwatchdog.h"
#include <QtMultiProcessSystem/QMpsWatchDog>

class RenderThreadWatchDog::Private
{
public:
    QMpsWatchDog watchDog;
    QMpsApplication application;
};

RenderThreadWatchDog::RenderThreadWatchDog(QQuickItem *parent)
    : QQuickItem(parent)
    , d(new Private)
{
    d->watchDog.setMethod("render-thread");
    connect(&d->watchDog, &QMpsWatchDog::watchDogManagerChanged, this, &RenderThreadWatchDog::watchDogManagerChanged);
    setFlag(ItemHasContents);
}

RenderThreadWatchDog::~RenderThreadWatchDog() = default;


QMpsWatchDogManager *RenderThreadWatchDog::watchDogManager() const
{
    return d->watchDog.watchDogManager();
}

void RenderThreadWatchDog::setWatchDogManager(QMpsWatchDogManager *watchDogManager)
{
    d->watchDog.setWatchDogManager(watchDogManager);
}

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
