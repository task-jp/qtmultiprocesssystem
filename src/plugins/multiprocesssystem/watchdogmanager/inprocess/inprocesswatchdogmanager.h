#ifndef INPROCESSWATCHDOGMANAGER_H
#define INPROCESSWATCHDOGMANAGER_H

#include <QtMultiProcessSystem/QMpsWatchDogManager>

class InProcessWatchDogManager : public QMpsWatchDogManager
{
    Q_OBJECT
public:
    explicit InProcessWatchDogManager(QObject *parent = nullptr);

protected:
    static InProcessWatchDogManager *server;
};

class InProcessWatchDogManagerServer : public InProcessWatchDogManager
{
    Q_OBJECT
public:
    explicit InProcessWatchDogManagerServer(QObject *parent = nullptr);
    ~InProcessWatchDogManagerServer() override;

public Q_SLOTS:
    void started(const QMpsApplication &application) override;
    void finished(const QMpsApplication &application) override;
    void ping(const QString &method, const QMpsApplication &application, uint serial) override;
    void pong(const QString &method, const QMpsApplication &application, uint serial) override;
    void pang(const QString &method, const QMpsApplication &application) override;

private:
    class Private;
    QScopedPointer<Private> d;
};

class InProcessWatchDogManagerClient : public InProcessWatchDogManager
{
    Q_OBJECT
public:
    explicit InProcessWatchDogManagerClient(QObject *parent = nullptr);

public Q_SLOTS:
    void started(const QMpsApplication &application) override;
    void finished(const QMpsApplication &application) override;
    void ping(const QString &method, const QMpsApplication &application, uint serial) override;
    void pong(const QString &method, const QMpsApplication &application, uint serial) override;
    void pang(const QString &method, const QMpsApplication &application) override;
};

#endif // INPROCESSWATCHDOGMANAGER_H
