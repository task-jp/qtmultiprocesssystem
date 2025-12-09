#ifndef QMPSAPPLICATIONPLUGIN_H
#define QMPSAPPLICATIONPLUGIN_H

#include <QtMultiProcessSystem/multiprocesssystem_global.h>
#include <QtCore/QObject>

QT_BEGIN_NAMESPACE

#define QMpsApplicationFactoryInterface_iid \
    "org.qt-project.Qt.QMpsApplicationFactoryInterface"

class MULTIPROCESSSYSTEM_EXPORT QMpsApplicationPlugin : public QObject
{
    Q_OBJECT
public:
    explicit QMpsApplicationPlugin(QObject *parent = nullptr);

    virtual QObject *create(const QString &key, QObject *parent = nullptr);
};

QT_END_NAMESPACE

#endif // QMPSAPPLICATIONPLUGIN_H
