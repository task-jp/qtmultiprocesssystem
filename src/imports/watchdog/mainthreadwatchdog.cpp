#include "mainthreadwatchdog.h"
#include <QtMultiProcessSystem/QMpsWatchDogManager>

class MainThreadWatchDog::Private
{
public:
    QMpsApplication application;
};

MainThreadWatchDog::MainThreadWatchDog(QObject *parent)
    : QMpsWatchDog(parent)
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
    QMpsWatchDog::pang(d->application);
}
