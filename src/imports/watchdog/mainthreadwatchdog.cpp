#include "mainthreadwatchdog.h"
#include <QtCore/QTimer>

class MainThreadWatchDog::Private
{
public:
    QMpsApplication application;
};

MainThreadWatchDog::MainThreadWatchDog(QObject *parent)
    : QMpsWatchDog(parent)
    , d(new Private)
{
    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() {
        if (d->application.isValid())
            pang();
    });
    timer->start(1000);
}

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
