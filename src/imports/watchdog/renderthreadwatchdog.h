#ifndef RENDERTHREADWATCHDOG_H
#define RENDERTHREADWATCHDOG_H

#include <QtQuick/QQuickItem>
#include <QtMultiProcessSystem/QMpsApplication>

class RenderThreadWatchDog : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QMpsApplication application READ application WRITE setApplication NOTIFY applicationChanged)
    Q_DISABLE_COPY(RenderThreadWatchDog)
public:
    explicit RenderThreadWatchDog(QQuickItem *parent = nullptr);
    ~RenderThreadWatchDog() override;

    QMpsApplication application() const;

public slots:
    void setApplication(const QMpsApplication &application);
    void pang();

private slots:
    void pangInternal();

signals:
    void applicationChanged(const QMpsApplication &application);

protected:
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *) override;

private:
    class Private;
    QScopedPointer<Private> d;
};

#endif // RENDERTHREADWATCHDOG_H
