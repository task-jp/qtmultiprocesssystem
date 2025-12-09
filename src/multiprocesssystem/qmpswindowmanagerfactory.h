#ifndef QMPSWINDOWMANAGERFACTORY_H
#define QMPSWINDOWMANAGERFACTORY_H

#include <QtMultiProcessSystem/qmpsabstractmanagerfactory.h>

QT_BEGIN_NAMESPACE

class QObject;
class QMpsWindowManager;

class MULTIPROCESSSYSTEM_EXPORT QMpsWindowManagerFactory : public QMpsAbstractManagerFactory
{
public:
    static QStringList keys();
    static QMpsWindowManager *create(const QString &key, Type type, QObject *parent = nullptr);
};

QT_END_NAMESPACE

#endif // QMPSWINDOWMANAGERFACTORY_H
