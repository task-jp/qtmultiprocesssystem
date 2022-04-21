#ifndef SYSTEMDAPPLICATIONMANAGER_H
#define SYSTEMDAPPLICATIONMANAGER_H

#include <QtMultiProcessSystem/QMpsApplicationManager>

class SystemdApplicationManager : public QMpsApplicationManager
{
    Q_OBJECT
public:
    explicit SystemdApplicationManager(QObject *parent, Type type);
    ~SystemdApplicationManager() override;

private:
    class Private;
    QScopedPointer<Private> d;
};

#endif // SYSTEMDAPPLICATIONMANAGER_H
