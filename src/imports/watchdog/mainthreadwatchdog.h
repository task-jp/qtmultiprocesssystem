#ifndef MAINTHREADWATCHDOG_H
#define MAINTHREADWATCHDOG_H

#include <QtCore/QObject>
#include <QtQml/qqml.h>
#include <QtMultiProcessSystem/QMpsApplication>

class MainThreadWatchDog : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QMpsApplication application READ application WRITE setApplication NOTIFY applicationChanged)
    Q_DISABLE_COPY(MainThreadWatchDog)
public:
    explicit MainThreadWatchDog(QObject *parent = nullptr);
    ~MainThreadWatchDog() override;

    QMpsApplication application() const;

public slots:
    void setApplication(const QMpsApplication &application);
    void pang();

signals:
    void applicationChanged(const QMpsApplication &application);

private:
    class Private;
    QScopedPointer<Private> d;
};

#endif // MAINTHREADWATCHDOG_H
