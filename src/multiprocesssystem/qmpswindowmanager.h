#ifndef QMPSWINDOWMANAGER_H
#define QMPSWINDOWMANAGER_H

#include "multiprocesssystem_global.h"
#include <QtCore/QObject>

class MULTIPROCESSSYSTEM_EXPORT QMpsWindowManager : public QObject
{
    Q_OBJECT
public:
    explicit QMpsWindowManager(QObject *parent = nullptr);
};

#endif // QMPSWINDOWMANAGER_H
