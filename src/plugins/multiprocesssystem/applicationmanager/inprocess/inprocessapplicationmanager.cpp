#include "inprocessapplicationmanager.h"
#include <QtMultiProcessSystem/QMpsApplicationFactory>
#include <QDebug>

class InProcessApplicationManager::Private
{
public:
    const QString category = qEnvironmentVariable("QT_MULTIPROCESSSYSTEM_APPLICATION_CATEGORY", "example");
    QHash<QMpsApplication, QObject *> processMap;
};

InProcessApplicationManager::InProcessApplicationManager(QObject *parent, Type type)
    : QMpsApplicationManager(parent, type)
    , d(new Private)
{
    connect(this, &InProcessApplicationManager::doExec, this, [this](const QMpsApplication &application, const QStringList &arguments) {
        if (!application.isValid()) {
            return;
        }
        if (d->processMap.contains(application)) {
            emit activated(application, arguments);
        } else {
            auto object = QMpsApplicationFactory::load(d->category + "/" + application.key(), this);
            if (object) {
                d->processMap.insert(application, object);
                setApplicationStatus(application, "created");
                setApplicationStatus(application, "started");
                emit activated(application, arguments);
            } else {
                qWarning() << "launching" << application.key() << "in" << d->category << "failed";
            }
        }
    });
}

InProcessApplicationManager::~InProcessApplicationManager() = default;
