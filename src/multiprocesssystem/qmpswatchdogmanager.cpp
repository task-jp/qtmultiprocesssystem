#include "qmpswatchdogmanager.h"

static QMpsWatchDogManager *mwdm = nullptr;

QMpsWatchDogManager *QMpsWatchDogManager::instance()
{
    return mwdm;
}

QMpsWatchDogManager::QMpsWatchDogManager(QObject *parent)
    : QObject(parent)
{
    Q_ASSERT(!mwdm);
    mwdm = this;
}
