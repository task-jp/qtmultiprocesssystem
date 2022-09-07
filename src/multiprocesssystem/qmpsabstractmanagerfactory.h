#ifndef QMPSABSTRACTMANAGERFACTORY_H
#define QMPSABSTRACTMANAGERFACTORY_H

#include "multiprocesssystem_global.h"
#include <QtCore/QString>

class QMpsAbstractManagerFactory
{
public:
    enum Type {
        Unknown,
        Server,
        Client,
    };
};

#endif // QMPSABSTRACTMANAGERFACTORY_H
