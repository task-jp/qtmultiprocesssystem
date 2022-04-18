#ifndef QMPSWATCHDOG_H
#define QMPSWATCHDOG_H

#include "multiprocesssystem_global.h"
#include "qmpswatchdogmanager.h"
#include "qmpsapplication.h"

class MULTIPROCESSSYSTEM_EXPORT QMpsWatchDog : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QMpsWatchDogManager *manager READ watchDogManager WRITE setWatchDogManager NOTIFY watchDogManagerChanged)
    Q_PROPERTY(QString method READ method WRITE setMethod NOTIFY methodChanged)
public:
    explicit QMpsWatchDog(QObject *parent = nullptr);
    ~QMpsWatchDog() override;

    QMpsWatchDogManager *watchDogManager() const;
    QString method() const;

public Q_SLOTS:
    void setWatchDogManager(QMpsWatchDogManager *watchDogManager);
    void setMethod(const QString &method);
    void ping(const QMpsApplication &app, uint serial);
    void pong(const QMpsApplication &app, uint serial);
    void pang(const QMpsApplication &app);

Q_SIGNALS:
    void watchDogManagerChanged(QMpsWatchDogManager *watchDogManager);
    void methodChanged(const QString &method);

private:
    class Private;
    QScopedPointer<Private> d;
};

#endif // QMPSWATCHDOG_H
