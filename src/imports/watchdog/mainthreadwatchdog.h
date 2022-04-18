#ifndef MAINTHREADWATCHDOG_H
#define MAINTHREADWATCHDOG_H

#include <QtCore/QObject>
#include <QtQml/qqml.h>
#include <QtMultiProcessSystem/QMpsWatchDogManager>
#include <QtMultiProcessSystem/QMpsApplication>

class MainThreadWatchDog : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QMpsWatchDogManager *manager READ watchDogManager WRITE setWatchDogManager NOTIFY watchDogManagerChanged)
    Q_PROPERTY(QMpsApplication application READ application WRITE setApplication NOTIFY applicationChanged)
    Q_DISABLE_COPY(MainThreadWatchDog)
public:
    explicit MainThreadWatchDog(QObject *parent = nullptr);
    ~MainThreadWatchDog() override;

    QMpsWatchDogManager *watchDogManager() const;
    QMpsApplication application() const;

public slots:
    void setWatchDogManager(QMpsWatchDogManager *watchDogManager);
    void setApplication(const QMpsApplication &application);
    void pang();

signals:
    void watchDogManagerChanged(QMpsWatchDogManager *watchDogManager);
    void applicationChanged(const QMpsApplication &application);

private:
    class Private;
    QScopedPointer<Private> d;
};

#endif // MAINTHREADWATCHDOG_H
