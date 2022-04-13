#ifndef XDGSHELLWATCHDOG_H
#define XDGSHELLWATCHDOG_H

#include <QtCore/QObject>
#include <QtQml/qqml.h>
#include <QtMultiProcessSystem/QMpsApplication>

class XdgShellWatchDog : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_DISABLE_COPY(XdgShellWatchDog)
public:
    explicit XdgShellWatchDog(QObject *parent = nullptr);
    ~XdgShellWatchDog() override;

public slots:
    void ping(const QMpsApplication &application, uint serial);
    void pong(uint serial);

private:
    class Private;
    QScopedPointer<Private> d;
};

#endif // XDGSHELLWATCHDOG_H
