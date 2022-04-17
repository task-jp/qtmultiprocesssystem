#ifndef INPROCESSAPPLICATIONMANAGER_H
#define INPROCESSAPPLICATIONMANAGER_H

#include <QtMultiProcessSystem/QMpsApplicationManager>

class InProcessApplicationManager : public QMpsApplicationManager
{
    Q_OBJECT
public:
    InProcessApplicationManager(QObject *parent, Type type);
};

#endif // INPROCESSAPPLICATIONMANAGER_H
