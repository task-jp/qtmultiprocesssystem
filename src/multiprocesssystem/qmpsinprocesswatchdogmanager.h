#ifndef QMPSINPROCESSWATCHDOGMANAGER_H
#define QMPSINPROCESSWATCHDOGMANAGER_H

#include "qmpswatchdogmanager.h"

// TODO: plugin-ize
class MULTIPROCESSSYSTEM_EXPORT QMpsInProcessWatchDogManager : public QMpsWatchDogManager
{
    Q_OBJECT
public:
    explicit QMpsInProcessWatchDogManager(QObject *parent = nullptr);
    ~QMpsInProcessWatchDogManager() override;

public Q_SLOTS:
    void started(const QMpsApplication &application) override;
    void finished(const QMpsApplication &application) override;
    void pingSent(const QString &method, const QMpsApplication &application, uint serial) override;
    void pongReceived(const QString &method, uint serial) override;

private:
    class Private;
    QScopedPointer<Private> d;
};

#endif // QMPSINPROCESSWATCHDOGMANAGER_H
