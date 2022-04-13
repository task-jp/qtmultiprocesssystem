#ifndef QMPSWATCHDOG_H
#define QMPSWATCHDOG_H

#include "multiprocesssystem_global.h"
#include "qmpsapplication.h"

class MULTIPROCESSSYSTEM_EXPORT QMpsWatchDog : public QObject
{
    Q_OBJECT
public:
    explicit QMpsWatchDog(const QString &method, QObject *parent = nullptr);

public Q_SLOTS:
    void ping(const QMpsApplication &app, uint serial);
    void pong(const QMpsApplication &app, uint serial);
    void pang(const QMpsApplication &app);

private:
    QString method;
};

#endif // QMPSWATCHDOG_H
