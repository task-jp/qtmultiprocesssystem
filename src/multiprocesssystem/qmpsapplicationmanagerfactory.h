#ifndef QMPSAPPLICATIONMANAGERFACTORY_H
#define QMPSAPPLICATIONMANAGERFACTORY_H

#include "qmpsabstractmanagerfactory.h"

class QObject;
class QMpsApplicationManager;

class MULTIPROCESSSYSTEM_EXPORT QMpsApplicationManagerFactory : public QMpsAbstractManagerFactory
{
public:
    static QStringList keys();
    static QMpsApplicationManager *create(const QString &key, Type type, const QString &prefix, QObject *parent = nullptr);
};

#endif // QMPSAPPLICATIONMANAGERFACTORY_H
