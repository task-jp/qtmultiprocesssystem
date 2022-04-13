#ifndef XDGSHELLWATCHDOG_H
#define XDGSHELLWATCHDOG_H

#include <QtCore/QObject>
#include <QtQml/qqml.h>
#include <QtMultiProcessSystem/QMpsApplication>
#include <QtMultiProcessSystem/QMpsWatchDog>

class XdgShellWatchDog : public QMpsWatchDog
{
    Q_OBJECT
    QML_ELEMENT
    Q_DISABLE_COPY(XdgShellWatchDog)
public:
    explicit XdgShellWatchDog(QObject *parent = nullptr);
    ~XdgShellWatchDog() override;

    QString method() const override { return QStringLiteral("xdgshell"); }

public slots:
    void pingSent(const QMpsApplication &application, uint serial);
    void pongReceived(uint serial);

private:
    class Private;
    QScopedPointer<Private> d;
};

#endif // XDGSHELLWATCHDOG_H
