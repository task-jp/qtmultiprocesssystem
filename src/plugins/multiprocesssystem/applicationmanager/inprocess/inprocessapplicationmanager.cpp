#include "inprocessapplicationmanager.h"
#include <QtMultiProcessSystem/QMpsApplicationFactory>
#include <QDebug>

class InProcessApplicationManager::Private
{
public:
    QHash<QMpsApplication, QObject *> processMap;
};

InProcessApplicationManager::InProcessApplicationManager(QObject *parent, Type type)
    : QMpsApplicationManager(parent, type)
    , d(new Private)
{
    connect(this, &InProcessApplicationManager::doExec, this, [this](const QMpsApplication &application) {
        static const QString category = qEnvironmentVariable("QT_MULTIPROCESSSYSTEM_APPLICATION_CATEGORY", "example1");
        if (d->processMap.contains(application)) {
            emit activated(application);
        } else {
            auto object = QMpsApplicationFactory::load(category + application.key(), this);
            if (object) {
                d->processMap.insert(application, object);
                emit activated(application);
            } else {
                qWarning() << "launching" << application.key() << "in" << category << "failed";
            }
        }
    });
}

InProcessApplicationManager::~InProcessApplicationManager() = default;
