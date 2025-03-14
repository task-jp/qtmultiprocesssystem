#ifndef QMPSABSTRACTDBUSINTERFACE_H
#define QMPSABSTRACTDBUSINTERFACE_H

#include "qmpsabstractipcinterface.h"

#include <QtCore/QDateTime>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QMetaProperty>
#include <QtCore/QMetaType>
#include <QtDBus/QDBusArgument>
#include <QtGui/QColor>

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include "qmpsapplication.h"
#endif

class MULTIPROCESSSYSTEM_EXPORT QMpsAbstractDBusInterface : public QMpsAbstractIpcInterface
{
    Q_OBJECT
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
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
            const int type = property.type();
#else
            const int type = property.typeId();
#endif
            const auto key = QString::fromLatin1(property.name());
            const auto value = property.readOnGadget(&gadget);
            switch (type) {
            case QMetaType::Bool:
                argument << value.toBool();
                break;
            case QMetaType::Int:
                argument << value.toInt();
                break;
            case QMetaType::LongLong:
                argument << value.toLongLong();
                break;
            case QMetaType::QString:
            case QMetaType::QColor:
            case QMetaType::QUrl:
            case QMetaType::QDateTime:
                argument << value.toString();
                break;
            case QMetaType::QJsonObject:
                argument << QJsonDocument(value.toJsonObject()).toJson(QJsonDocument::Compact);
                break;
            default:
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
                if (type == qMetaTypeId<QMpsApplication::Attributes>()) {
                    argument << value.toInt();
                    break;
                }
#endif
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
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
            const int type = property.type();
#else
            const int type = property.typeId();
#endif
            const auto key = QString::fromLatin1(property.name());
            QVariant value;
            switch (type) {
            case QMetaType::Bool:
                value = qdbus_cast<bool>(argument);
                break;
            case QMetaType::Int:
                value = qdbus_cast<int>(argument);
                break;
            case QMetaType::LongLong:
                value = qdbus_cast<qint64>(argument);
                break;
            case QMetaType::QString:
                value = qdbus_cast<QString>(argument);
                break;
            case QMetaType::QColor:
                value = QColor(qdbus_cast<QString>(argument));
                break;
            case QMetaType::QUrl:
                value = QUrl(qdbus_cast<QString>(argument));
                break;
            case QMetaType::QDateTime:
                value = QDateTime::fromString(qdbus_cast<QString>(argument), Qt::ISODateWithMs);
                break;
            case QMetaType::QJsonObject:
                value = QJsonDocument::fromJson(qdbus_cast<QByteArray>(argument)).object();
                break;
            default:
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
                if (type == qMetaTypeId<QMpsApplication::Attributes>()) {
                    value = qdbus_cast<int>(argument);
                    break;
                }
#endif
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
