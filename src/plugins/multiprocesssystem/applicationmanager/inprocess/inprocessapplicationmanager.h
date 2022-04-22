#ifndef INPROCESSAPPLICATIONMANAGER_H
#define INPROCESSAPPLICATIONMANAGER_H

#include <QtMultiProcessSystem/QMpsApplicationManager>

class InProcessApplicationManager : public QMpsApplicationManager
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "local.ApplicationManager")
public:
    InProcessApplicationManager(QObject *parent, Type type);
    ~InProcessApplicationManager() override;

private:
    class Private;
    QScopedPointer<Private> d;
};

#endif // INPROCESSAPPLICATIONMANAGER_H
