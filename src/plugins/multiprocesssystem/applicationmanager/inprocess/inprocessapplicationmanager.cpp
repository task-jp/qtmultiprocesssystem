#include "inprocessapplicationmanager.h"

InProcessApplicationManager *InProcessApplicationManager::server = nullptr;

InProcessApplicationManager::InProcessApplicationManager(const QString &prefix, QObject *parent)
    : QMpsApplicationManager(prefix, parent)
{}

InProcessApplicationManagerServer::InProcessApplicationManagerServer(const QString &prefix, QObject *parent)
    : InProcessApplicationManager(prefix, parent)
{
    server = this;
}

InProcessApplicationManagerClient::InProcessApplicationManagerClient(const QString &prefix, QObject *parent)
    : InProcessApplicationManager(prefix, parent)
{
    connect(server, &InProcessApplicationManager::currentChanged, this, &InProcessApplicationManager::currentChanged);
    connect(server, &InProcessApplicationManager::activated, this, &InProcessApplicationManager::activated);
}

QMpsApplication InProcessApplicationManagerClient::current() const
{
    return server->current();
}

void InProcessApplicationManagerClient::setCurrent(const QMpsApplication &current)
{
    server->setCurrent(current);
}

void InProcessApplicationManagerClient::exec(const QString &key)
{
    server->exec(key);
}
