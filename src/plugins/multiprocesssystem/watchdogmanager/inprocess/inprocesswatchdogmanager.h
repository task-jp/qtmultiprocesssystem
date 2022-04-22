#ifndef INPROCESSWATCHDOGMANAGER_H
#define INPROCESSWATCHDOGMANAGER_H

#include <QtMultiProcessSystem/QMpsWatchDogManager>

class InProcessWatchDogManager : public QMpsWatchDogManager
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "local.WatchDogManager")
public:
    explicit InProcessWatchDogManager(QObject *parent = nullptr, Type type = Client);
    ~InProcessWatchDogManager() override;

private:
    class Private;
    QScopedPointer<Private> d;
};

#endif // INPROCESSWATCHDOGMANAGER_H
