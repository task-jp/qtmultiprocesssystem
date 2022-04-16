#ifndef QMPSABSTRACTDBUSINTERFACE_H
#define QMPSABSTRACTDBUSINTERFACE_H

#include "qmpsabstractipcinterface.h"

class MULTIPROCESSSYSTEM_EXPORT QMpsAbstractDBusInterface : public QMpsAbstractIpcInterface
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "local.QMpsAbstractDBusInterface")
public:
    explicit QMpsAbstractDBusInterface(QObject *parent = nullptr, Type = Client);
    ~QMpsAbstractDBusInterface() override;

    bool init() override;

private:
    class Private;
    QScopedPointer<Private> d;
};

#endif // QMPSABSTRACTDBUSINTERFACE_H
