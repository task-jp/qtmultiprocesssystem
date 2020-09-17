#ifndef QMPSAPPLICATIONFACTORY_H
#define QMPSAPPLICATIONFACTORY_H

#include "multiprocesssystem_global.h"

#include <QtCore/QJsonObject>

class QMpsApplication;
class QMpsApplicationManager;

class MULTIPROCESSSYSTEM_EXPORT QMpsApplicationFactory
{
public:
    static QList<QJsonObject> apps();
    static QStringList keys();
    static QMpsApplication *load(const QString &key, QObject *parent = nullptr);
};

#endif // QMPSAPPLICATIONFACTORY_H
