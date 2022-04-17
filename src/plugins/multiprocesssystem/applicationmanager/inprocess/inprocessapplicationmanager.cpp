#include "inprocessapplicationmanager.h"

InProcessApplicationManager::InProcessApplicationManager(QObject *parent, Type type)
    : QMpsApplicationManager(parent, type)
{
    connect(this, &InProcessApplicationManager::doExec, this, [this](const QMpsApplication &application) {
        emit activated(application);
    });
}
