#include "qmpsapplicationplugin.h"

QMpsApplicationPlugin::QMpsApplicationPlugin(QObject *parent)
    : QObject(parent)
{}

QObject *QMpsApplicationPlugin::create(const QString &key, QObject *parent)
{
    Q_UNUSED(key);
    Q_UNUSED(parent);
    return nullptr;
}
