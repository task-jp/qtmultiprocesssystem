#ifndef INPROCESSAPPLICATIONMANAGER_H
#define INPROCESSAPPLICATIONMANAGER_H

#include <QtMultiProcessSystem/QMpsApplicationManager>

class InProcessApplicationManager : public QMpsApplicationManager
{
    Q_OBJECT
public:
    InProcessApplicationManager(const QString &prefix, QObject *parent = nullptr);

protected:
    static InProcessApplicationManager *server;
};

class InProcessApplicationManagerServer : public InProcessApplicationManager
{
    Q_OBJECT
public:
    InProcessApplicationManagerServer(const QString &prefix, QObject *parent = nullptr);
};

class InProcessApplicationManagerClient : public InProcessApplicationManager
{
    Q_OBJECT
public:
    InProcessApplicationManagerClient(const QString &prefix, QObject *parent = nullptr);

    QMpsApplication current() const override;

public slots:
    void setCurrent(const QMpsApplication &current) override;
    void exec(const QString &key) override;
};

#endif // INPROCESSAPPLICATIONMANAGER_H
