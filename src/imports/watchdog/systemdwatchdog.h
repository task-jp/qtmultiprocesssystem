#ifndef SYSTEMDWATCHDOG_H
#define SYSTEMDWATCHDOG_H

#include <QtCore/QObject>
#include <QtQml/qqml.h>

class SystemdWatchDog : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_DISABLE_COPY(SystemdWatchDog)
public:
    explicit SystemdWatchDog(QObject *parent = nullptr);
    ~SystemdWatchDog() override;

public slots:
    void pang();

private:
    class Private;
    QScopedPointer<Private> d;
};

#endif // SYSTEMDWATCHDOG_H
