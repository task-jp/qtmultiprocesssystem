#ifndef QPROCESSAPPLICATIONMANAGER_H
#define QPROCESSAPPLICATIONMANAGER_H

#include <QtMultiProcessSystem/QMpsApplicationManager>

class QProcessApplicationManager : public QMpsApplicationManager
{
    Q_OBJECT
public:
    explicit QProcessApplicationManager(QObject *parent, Type type);
    ~QProcessApplicationManager() override;

private:
    class Private;
    QScopedPointer<Private> d;
};

#endif // QPROCESSAPPLICATIONMANAGER_H
