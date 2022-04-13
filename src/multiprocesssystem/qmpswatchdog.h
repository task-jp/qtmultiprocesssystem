#ifndef QMPSWATCHDOG_H
#define QMPSWATCHDOG_H

#include "multiprocesssystem_global.h"
#include "qmpsapplication.h"

class MULTIPROCESSSYSTEM_EXPORT QMpsWatchDog : public QObject
{
    Q_OBJECT
public:
    explicit QMpsWatchDog(QObject *parent = nullptr);

    virtual QString method() const = 0;

public Q_SLOTS:
    void ping(const QMpsApplication &app, uint serial);
    void pong(const QMpsApplication &app, uint serial);
    void pang(const QMpsApplication &app);
};

#endif // QMPSWATCHDOG_H
