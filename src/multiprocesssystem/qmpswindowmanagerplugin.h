#ifndef QMPSWINDOWMANAGERPLUGIN_H
#define QMPSWINDOWMANAGERPLUGIN_H

#include <QtMultiProcessSystem/multiprocesssystem_global.h>
#include <QtCore/QObject>
#include <QtMultiProcessSystem/qmpsabstractmanagerfactory.h>

QT_BEGIN_NAMESPACE

class QMpsWindowManager;

#define QMpsWindowManagerFactoryInterface_iid \
    "org.qt-project.Qt.QMpsWindowManagerFactoryInterface"

class MULTIPROCESSSYSTEM_EXPORT QMpsWindowManagerPlugin : public QObject
{
    Q_OBJECT
public:
    explicit QMpsWindowManagerPlugin(QObject *parent = nullptr);

    virtual QMpsWindowManager *create(const QString &key, QMpsAbstractManagerFactory::Type type, QObject *parent = nullptr) = 0;
};

QT_END_NAMESPACE

#endif // QMPSWINDOWMANAGERPLUGIN_H
