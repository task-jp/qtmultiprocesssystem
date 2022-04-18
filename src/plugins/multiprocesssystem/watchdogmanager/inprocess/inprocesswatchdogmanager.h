#ifndef INPROCESSWATCHDOGMANAGER_H
#define INPROCESSWATCHDOGMANAGER_H

#include <QtMultiProcessSystem/QMpsWatchDogManager>

class InProcessWatchDogManager : public QMpsWatchDogManager
{
    Q_OBJECT
public:
    explicit InProcessWatchDogManager(QObject *parent = nullptr, Type type = Client);
    ~InProcessWatchDogManager() override;

private:
    class Private;
    QScopedPointer<Private> d;
};

#endif // INPROCESSWATCHDOGMANAGER_H
