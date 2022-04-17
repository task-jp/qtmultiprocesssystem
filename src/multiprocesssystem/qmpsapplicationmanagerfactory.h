#ifndef QMPSAPPLICATIONMANAGERFACTORY_H
#define QMPSAPPLICATIONMANAGERFACTORY_H

#include <QtCore/QObject>
#include "qmpsabstractipcinterface.h"
class QMpsApplicationManager;

class MULTIPROCESSSYSTEM_EXPORT QMpsApplicationManagerFactory : public QObject
{
public:
    static QStringList keys();
    static QMpsApplicationManager *create(const QString &key, QObject *parent = nullptr, QMpsAbstractManagerFactory::Type type = QMpsAbstractManagerFactory::Client);
};

#endif // QMPSAPPLICATIONMANAGERFACTORY_H
