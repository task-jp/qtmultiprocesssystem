#include "mainthreadwatchdog.h"
#include <QtMultiProcessSystem/QMpsWatchDog>

class MainThreadWatchDog::Private
{
public:
    QMpsWatchDog watchDog;
    QMpsApplication application;
};

MainThreadWatchDog::MainThreadWatchDog(QObject *parent)
    : QObject(parent)
    , d(new Private)
{
    d->watchDog.setMethod("main-thread");
    connect(&d->watchDog, &QMpsWatchDog::watchDogManagerChanged, this, &MainThreadWatchDog::watchDogManagerChanged);
}

MainThreadWatchDog::~MainThreadWatchDog() = default;

QMpsWatchDogManager *MainThreadWatchDog::watchDogManager() const
{
    return d->watchDog.watchDogManager();
}

void MainThreadWatchDog::setWatchDogManager(QMpsWatchDogManager *watchDogManager)
{
    d->watchDog.setWatchDogManager(watchDogManager);
}

QMpsApplication MainThreadWatchDog::application() const
{
    return d->application;
}

void MainThreadWatchDog::setApplication(const QMpsApplication &application)
{
    if (d->application == application) return;
    d->application = application;
    emit applicationChanged(application);
}

void MainThreadWatchDog::pang()
{
    d->watchDog.pang(d->application);
}
