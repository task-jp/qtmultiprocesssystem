#include "qmpsapplicationplugin.h"

QMpsApplicationPlugin::QMpsApplicationPlugin(QObject *parent)
    : QObject(parent)
{}

#include <QDebug>

QObject *QMpsApplicationPlugin::create(const QString &key, QObject *parent)
{
    qDebug() << key << parent;
    Q_UNUSED(key);
    Q_UNUSED(parent);
    return this;
}
