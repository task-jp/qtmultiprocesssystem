#ifndef INPROCESSAPPLICATIONMANAGER_H
#define INPROCESSAPPLICATIONMANAGER_H

#include <QtMultiProcessSystem/QMpsApplicationManager>

class InProcessApplicationManager : public QMpsApplicationManager
{
    Q_OBJECT
public:
    InProcessApplicationManager(QObject *parent = nullptr);

protected:
    static InProcessApplicationManager *server;
};

class InProcessApplicationManagerServer : public InProcessApplicationManager
{
    Q_OBJECT
public:
    InProcessApplicationManagerServer(QObject *parent = nullptr);
};

class InProcessApplicationManagerClient : public InProcessApplicationManager
{
    Q_OBJECT
public:
    InProcessApplicationManagerClient(QObject *parent = nullptr);

public slots:
    void exec(int id, const QString &name) override;
};

#endif // INPROCESSAPPLICATIONMANAGER_H
