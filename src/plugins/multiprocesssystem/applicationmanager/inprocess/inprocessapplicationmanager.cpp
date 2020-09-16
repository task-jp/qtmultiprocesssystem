#include "inprocessapplicationmanager.h"

InProcessApplicationManager *InProcessApplicationManager::server = nullptr;

InProcessApplicationManager::InProcessApplicationManager(QObject *parent)
    : QMpsApplicationManager(parent)
{}

InProcessApplicationManagerServer::InProcessApplicationManagerServer(QObject *parent)
    : InProcessApplicationManager(parent)
{
    server = this;
}

InProcessApplicationManagerClient::InProcessApplicationManagerClient(QObject *parent)
    : InProcessApplicationManager(parent)
{
    connect(server, &InProcessApplicationManager::activated, this, &InProcessApplicationManager::activated);
}

void InProcessApplicationManagerClient::exec(int id, const QString &name)
{
    server->exec(id, name);
}
