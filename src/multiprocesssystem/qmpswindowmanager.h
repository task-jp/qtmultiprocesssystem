#ifndef QMPSWINDOWMANAGER_H
#define QMPSWINDOWMANAGER_H

#include <QtMultiProcessSystem/multiprocesssystem_global.h>
#include <QtCore/QObject>

QT_BEGIN_NAMESPACE

class MULTIPROCESSSYSTEM_EXPORT QMpsWindowManager : public QObject
{
    Q_OBJECT
public:
    explicit QMpsWindowManager(QObject *parent = nullptr);
};

QT_END_NAMESPACE

#endif // QMPSWINDOWMANAGER_H
