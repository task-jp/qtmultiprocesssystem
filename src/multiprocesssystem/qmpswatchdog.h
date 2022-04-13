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
    virtual void pingSent(const QMpsApplication &app, uint serial) = 0;
    virtual void pongReceived(uint serial) = 0;

protected:
    void pingSentImpl(const QMpsApplication &app, uint serial);
    void pongReceivedImpl(uint serial);
};

#endif // QMPSWATCHDOG_H
