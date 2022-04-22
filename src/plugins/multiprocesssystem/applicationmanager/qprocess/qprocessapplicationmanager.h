#ifndef QPROCESSAPPLICATIONMANAGER_H
#define QPROCESSAPPLICATIONMANAGER_H

#include <QtMultiProcessSystem/QMpsApplicationManager>

class QProcessApplicationManager : public QMpsApplicationManager
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "local.ApplicationManager")
public:
    explicit QProcessApplicationManager(QObject *parent, Type type);
    ~QProcessApplicationManager() override;

private:
    class Private;
    QScopedPointer<Private> d;
};

#endif // QPROCESSAPPLICATIONMANAGER_H
