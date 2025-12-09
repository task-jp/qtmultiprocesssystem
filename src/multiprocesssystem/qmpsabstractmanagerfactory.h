#ifndef QMPSABSTRACTMANAGERFACTORY_H
#define QMPSABSTRACTMANAGERFACTORY_H

#include <QtMultiProcessSystem/multiprocesssystem_global.h>
#include <QtCore/QString>

QT_BEGIN_NAMESPACE

class QMpsAbstractManagerFactory
{
public:
    enum Type {
        Unknown,
        Server,
        Client,
    };
};

QT_END_NAMESPACE

#endif // QMPSABSTRACTMANAGERFACTORY_H
