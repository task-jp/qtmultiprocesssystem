#ifndef QMPSABSTRACTDBUSINTERFACE_H
#define QMPSABSTRACTDBUSINTERFACE_H

#include "qmpsabstractipcinterface.h"

#include <QtCore/QDateTime>
#include <QtCore/QMetaProperty>
#include <QtCore/QMetaType>
#include <QtDBus/QDBusArgument>

class MULTIPROCESSSYSTEM_EXPORT QMpsAbstractDBusInterface : public QMpsAbstractIpcInterface
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "local.QMpsAbstractDBusInterface")
public:
    explicit QMpsAbstractDBusInterface(QObject *parent = nullptr, Type = Client);
    ~QMpsAbstractDBusInterface() override;

    bool init() override;

    template<class T>
    static QDBusArgument &fromGadget(QDBusArgument &argument, const T &gadget) {
        argument.beginStructure();
        const auto mo = gadget.staticMetaObject;
        for (int i = 0; i < mo.propertyCount(); i++) {
            auto property = mo.property(i);
            const auto type = property.type();
            auto key = QString::fromLatin1(property.name());
            auto value = property.readOnGadget(&gadget);
            switch (type) {
            case QVariant::Bool:
                argument << value.toBool();
                break;
            case QVariant::Int:
                argument << value.toInt();
                break;
            case QVariant::String:
            case QVariant::Color:
            case QVariant::Url:
            case QVariant::DateTime:
                argument << value.toString();
                break;
            default:
                qWarning() << type << key << value << "not supported";
                break;
            }
        }
        argument.endStructure();
        return argument;
    }

    template<class T>
    static const QDBusArgument &toGadget(const QDBusArgument &argument, T &gadget)
    {
        argument.beginStructure();
        const auto mo = gadget.staticMetaObject;
        for (int i = 0; i < mo.propertyCount(); i++) {
            const auto property = mo.property(i);
            const auto type = property.type();
            auto key = QString::fromLatin1(property.name());
            QVariant value;
            switch (type) {
            case QVariant::Bool:
                value = qdbus_cast<bool>(argument);
                break;
            case QVariant::Int:
                value = qdbus_cast<int>(argument);
                break;
            case QVariant::String:
                value = qdbus_cast<QString>(argument);
                break;
            case QVariant::Color:
                value = QColor(qdbus_cast<QString>(argument));
                break;
            case QVariant::Url:
                value = QUrl(qdbus_cast<QString>(argument));
                break;
            case QVariant::DateTime:
                value = QDateTime::fromString(qdbus_cast<QString>(argument), Qt::ISODateWithMs);
                break;
            default:
                qWarning() << type << key << value << "not supported";
                break;
            }
            property.writeOnGadget(&gadget, value);
        }
        argument.endStructure();
        return argument;
    }
private:
    class Private;
    QScopedPointer<Private> d;
};

#endif // QMPSABSTRACTDBUSINTERFACE_H
