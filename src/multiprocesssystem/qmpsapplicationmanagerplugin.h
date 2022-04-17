#ifndef QMPSAPPLICATIONMANAGERPLUGIN_H
#define QMPSAPPLICATIONMANAGERPLUGIN_H

#include "multiprocesssystem_global.h"
#include <QtCore/QObject>
#include "qmpsabstractipcinterface.h"

class QMpsApplicationManager;

#define QMpsApplicationManagerFactoryInterface_iid \
    "org.qt-project.Qt.QMpsApplicationManagerFactoryInterface"

class MULTIPROCESSSYSTEM_EXPORT QMpsApplicationManagerPlugin : public QObject
{
    Q_OBJECT
public:
    explicit QMpsApplicationManagerPlugin(QObject *parent = nullptr);

    virtual QMpsApplicationManager *create(const QString &key, QObject *parent = nullptr, QMpsAbstractIpcInterface::Type type = QMpsAbstractIpcInterface::Client) = 0;
};

#endif // QMPSAPPLICATIONMANAGERPLUGIN_H
