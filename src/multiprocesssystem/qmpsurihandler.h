#ifndef QMPSURIHANDLER_H
#define QMPSURIHANDLER_H

#include "multiprocesssystem_global.h"
#include "qmpsipcinterface.h"
#include "qmpsapplication.h"

class MULTIPROCESSSYSTEM_EXPORT QMpsUriHandler : public QMpsIpcInterface
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "local.UriHandler")
    Q_PROPERTY(QMpsApplication application READ application WRITE setApplication NOTIFY applicationChanged)
public:
    explicit QMpsUriHandler(QObject *parent = nullptr, Type type = Client);
    ~QMpsUriHandler() override;

    QMpsApplication application() const;

public Q_SLOTS:
    void setApplication(const QMpsApplication &application);

    void open(const QString &uri);

Q_SIGNALS:
    void applicationChanged(const QMpsApplication &application);

    void doOpen(const QString &uri);
    void requested(const QString &uri);

protected:
    QMpsAbstractIpcInterface *server() const override;

private:
    class Private;
    QScopedPointer<Private> d;
};

#endif // QMPSURIHANDLER_H
