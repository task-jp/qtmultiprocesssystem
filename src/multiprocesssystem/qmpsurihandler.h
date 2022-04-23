#ifndef QMPSURIHANDLER_H
#define QMPSURIHANDLER_H

#include "multiprocesssystem_global.h"
#include "qmpsipcinterface.h"
#include "qmpsapplication.h"

class MULTIPROCESSSYSTEM_EXPORT QMpsUriHandler : public QMpsIpcInterface
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "local.UriHandler")
    Q_PROPERTY(QMpsApplication application READ application CONSTANT)
public:
    explicit QMpsUriHandler(const QMpsApplication &application, QObject *parent = nullptr, Type type = Client);
    ~QMpsUriHandler() override;

    QMpsApplication application() const;

public Q_SLOTS:
    void open(const QString &uri);

Q_SIGNALS:
    void doOpen(const QString &uri);
    void requested(const QString &uri);

protected:
    QMpsAbstractIpcInterface *server() const override;

private:
    class Private;
    QScopedPointer<Private> d;
};

#endif // QMPSURIHANDLER_H
