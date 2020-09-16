#ifndef QMPSAPPLICATION_H
#define QMPSAPPLICATION_H

#include "multiprocesssystem_global.h"
#include <QtCore/QObject>

class MULTIPROCESSSYSTEM_EXPORT QMpsApplication : public QObject
{
    Q_OBJECT
public:
    explicit QMpsApplication(QObject *parent = nullptr);
};

#endif // QMPSAPPLICATION_H
