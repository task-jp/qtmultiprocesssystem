#ifndef QMPSAPPLICATIONMANAGERFACTORY_H
#define QMPSAPPLICATIONMANAGERFACTORY_H

#include <QtCore/QObject>
#include <QtMultiProcessSystem/qmpsabstractipcinterface.h>

QT_BEGIN_NAMESPACE

class QMpsApplicationManager;

class MULTIPROCESSSYSTEM_EXPORT QMpsApplicationManagerFactory : public QObject
{
public:
    static QStringList keys();
    static QMpsApplicationManager *create(const QString &key, QObject *parent = nullptr, QMpsAbstractManagerFactory::Type type = QMpsAbstractManagerFactory::Client);
};

QT_END_NAMESPACE

#endif // QMPSAPPLICATIONMANAGERFACTORY_H
