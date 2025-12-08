#ifndef RENDERTHREADWATCHDOG_H
#define RENDERTHREADWATCHDOG_H

#include <QtQuick/QQuickItem>
#include <QtQml/qqml.h>
#include <QtMultiProcessSystem/QMpsWatchDogManager>
#include <QtMultiProcessSystem/QMpsApplication>

class RenderThreadWatchDog : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
    QML_ADDED_IN_VERSION(1, 0)
    Q_PROPERTY(QMpsWatchDogManager *manager READ watchDogManager WRITE setWatchDogManager NOTIFY watchDogManagerChanged)
    Q_PROPERTY(QMpsApplication application READ application WRITE setApplication NOTIFY applicationChanged)
    Q_DISABLE_COPY(RenderThreadWatchDog)
public:
    explicit RenderThreadWatchDog(QQuickItem *parent = nullptr);
    ~RenderThreadWatchDog() override;

    QMpsWatchDogManager *watchDogManager() const;
    QMpsApplication application() const;

public slots:
    void setWatchDogManager(QMpsWatchDogManager *watchDogManager);
    void setApplication(const QMpsApplication &application);
    void pang();

private slots:
    void pangInternal();

signals:
    void watchDogManagerChanged(QMpsWatchDogManager *watchDogManager);
    void applicationChanged(const QMpsApplication &application);

protected:
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *) override;

private:
    class Private;
    QScopedPointer<Private> d;
};

#endif // RENDERTHREADWATCHDOG_H
