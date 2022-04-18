#ifndef QMPSWATCHDOGMANAGERPLUGIN_H
#define QMPSWATCHDOGMANAGERPLUGIN_H

#include "multiprocesssystem_global.h"
#include <QtCore/QObject>
#include "qmpsabstractipcinterface.h"

class QMpsWatchDogManager;

#define QMpsWatchDogManagerFactoryInterface_iid \
    "org.qt-project.Qt.QMpsWatchDogManagerFactoryInterface"

class MULTIPROCESSSYSTEM_EXPORT QMpsWatchDogManagerPlugin : public QObject
{
    Q_OBJECT
public:
    explicit QMpsWatchDogManagerPlugin(QObject *parent = nullptr);

    virtual QMpsWatchDogManager *create(const QString &key, QObject *parent = nullptr, QMpsAbstractIpcInterface::Type type = QMpsAbstractIpcInterface::Client) = 0;
};

#endif // QMPSWATCHDOGMANAGERPLUGIN_H
