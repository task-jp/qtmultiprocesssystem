#include "mainthreadwatchdog.h"
#include <QtMultiProcessSystem/QMpsWatchDog>

class MainThreadWatchDog::Private
{
public:
    QMpsWatchDog watchDog = QMpsWatchDog("main-thread");
    QMpsApplication application;
};

MainThreadWatchDog::MainThreadWatchDog(QObject *parent)
    : QObject(parent)
    , d(new Private)
{}

MainThreadWatchDog::~MainThreadWatchDog() = default;

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
