#include "qmpsapplication.h"

#include <QtCore/QJsonDocument>
#include <QtCore/QMetaProperty>

class QMpsApplication::Private : public QSharedData
{
public:
    int id = -1;
    QString key = QLatin1String("main");
    QJsonObject name;
    QColor theme;
    QUrl icon;
    QString area;
    bool systemUI = false;
    bool autoStart = false;
    bool daemon = false;
    QJsonObject uriHandlers;
};

QMpsApplication::QMpsApplication() : d(new Private)
{}

QMpsApplication::QMpsApplication(const QMpsApplication &other) : d(other.d)
{}

QMpsApplication &QMpsApplication::operator=(const QMpsApplication &other)
{
    if (this != &other)
        d.operator=(other.d);
    return *this;
}

QMpsApplication::~QMpsApplication() = default;

bool QMpsApplication::operator==(const QMpsApplication &other) const
{
    if (d == other.d) return true;
    return d->id == other.d->id;
}

int QMpsApplication::id() const
{
    return d->id;
}

void QMpsApplication::setID(int id)
{
    if (this->id() == id) return;
    d->id = id;
}

QString QMpsApplication::key() const
{
    return d->key;
}

void QMpsApplication::setKey(const QString &key)
{
    if (this->key() == key) return;
    d->key = key;
}

QJsonObject QMpsApplication::name() const
{
    return d->name;
}

void QMpsApplication::setName(const QJsonObject &name)
{
    if (this->name() == name) return;
    d->name = name;
}

QString QMpsApplication::i18nName() const
{
    // TODO: get lang from somewhere
    return d->name.contains("ja") ? d->name.value("ja").toString() : d->name.value("default").toString();
}

QColor QMpsApplication::theme() const
{
    return d->theme;
}

void QMpsApplication::setTheme(const QColor &theme)
{
    if (this->theme() == theme) return;
    d->theme = theme;
}

QUrl QMpsApplication::icon() const
{
    return d->icon;
}

void QMpsApplication::setIcon(const QUrl &icon)
{
    if (this->icon() == icon) return;
    d->icon = icon;
}

QString QMpsApplication::area() const
{
    return d->area;
}

void QMpsApplication::setArea(const QString &area)
{
    if (this->area() == area) return;
    d->area = area;
}

bool QMpsApplication::isSystemUI() const
{
    return d->systemUI;
}

void QMpsApplication::setSystemUI(bool systemUI)
{
    if (this->isSystemUI() == systemUI) return;
    d->systemUI = systemUI;
}

bool QMpsApplication::isAutoStart() const
{
    return d->autoStart;
}

void QMpsApplication::setAutoStart(bool autoStart)
{
    if (this->isAutoStart() == autoStart) return;
    d->autoStart = autoStart;
}

bool QMpsApplication::isDaemon() const
{
    return d->daemon;
}

void QMpsApplication::setDaemon(bool daemon)
{
    if (this->isDaemon() == daemon) return;
    d->daemon = daemon;
}

QJsonObject QMpsApplication::uriHandlers() const
{
    return d->uriHandlers;
}

void QMpsApplication::setUriHandlers(const QJsonObject &uriHandlers)
{
    if (this->uriHandlers() == uriHandlers) return;
    d->uriHandlers = uriHandlers;
}

bool QMpsApplication::isValid() const
{
    return d->id > -1;
}

QMpsApplication QMpsApplication::fromJson(const QJsonObject &json)
{
    QMpsApplication ret;
    for (int i = 0; i < ret.staticMetaObject.propertyCount(); i++) {
        const auto property = ret.staticMetaObject.property(i);
        const auto key = QString::fromLatin1(property.name());
        if (json.contains(key)) {
            const int type = property.type();
            const auto value = json.value(key);
            switch (type) {
            case QVariant::Bool:
                property.writeOnGadget(&ret, value.toBool());
                break;
            case QVariant::Int:
                property.writeOnGadget(&ret, value.toInt());
                break;
            case QVariant::String:
                property.writeOnGadget(&ret, value.toString());
                break;
            case QVariant::Color:
                property.writeOnGadget(&ret, QColor(value.toString()));
                break;
            case QVariant::Url:
                property.writeOnGadget(&ret, QUrl(value.toString()));
                break;
            case QVariant::DateTime:
                property.writeOnGadget(&ret, QDateTime::fromString(value.toString(), Qt::ISODateWithMs));
                break;
            case QMetaType::QJsonObject:
                property.writeOnGadget(&ret, value.toObject());
                break;
            default:
                qWarning() << type << key << value << "not supported";
                break;
            }
//        } else {
//            qWarning() << key << "not found in json";
        }
    }
    return ret;
}

QDataStream &operator<<(QDataStream &out, const QMpsApplication &application)
{
    const auto mo = application.staticMetaObject;
    for (int i = 0; i < mo.propertyCount(); i++) {
        const auto property = mo.property(i);
        const auto key = QString::fromLatin1(property.name());
        const auto value = property.readOnGadget(&application);
        out << value;
    }
    return out;
}

QDataStream &operator>>(QDataStream &in, QMpsApplication &application)
{
    const auto mo = application.staticMetaObject;
    for (int i = 0; i < mo.propertyCount(); i++) {
        const auto property = mo.property(i);
        const auto key = QString::fromLatin1(property.name());
        QVariant value;
        in >> value;
        property.writeOnGadget(&application, value);
    }
    return in;
}

QDebug operator<<(QDebug debug, const QMpsApplication &application)
{
    QDebugStateSaver saver(debug);
    debug.nospace() << "QMpsApplication {";
    const auto mo = application.staticMetaObject;
    bool first = true;
    for (int i = 0; i < mo.propertyCount(); i++) {
        const auto property = mo.property(i);
        if (!property.isWritable())
            continue;
        const int type = property.type();
        const auto key = QString::fromLatin1(property.name());
        const auto value = property.readOnGadget(&application);
        if (first)
            first = false;
        else
            debug << ";";
        debug.noquote() << " " << key << ": ";
        debug.quote();
        switch (type) {
        case QVariant::Bool:
            debug << value.toBool();
            break;
        case QVariant::Int:
            debug << value.toInt();
            break;
        case QVariant::String:
            debug << value.toString();
            break;
        case QVariant::Color:
            debug << QColor(value.toString());
            break;
        case QVariant::Url: {
            auto str = value.toString();
            if (str.length() > 15)
                str = str.left(12) + QStringLiteral("...");
            debug << QUrl(str);
            break; }
        case QVariant::DateTime:
            debug << QDateTime::fromString(value.toString(), Qt::ISODateWithMs);
            break;
        case QMetaType::QJsonObject:
            debug << QJsonDocument(value.toJsonObject()).toJson(QJsonDocument::Compact);
            break;
        default:
            debug << value;
            break;
        }
    }
    debug << " }";

    return debug;
}

uint qHash(const QMpsApplication &application, uint seed)
{
    return qHash(application.id(), seed);
}

#if defined(QT_DBUS_LIB)
#include "qmpsabstractdbusinterface.h"

QDBusArgument &operator<<(QDBusArgument &argument, const QMpsApplication &application)
{
    return QMpsAbstractDBusInterface::fromGadget(argument, application);
}

const QDBusArgument &operator>>(const QDBusArgument &argument, QMpsApplication &application)
{
    return QMpsAbstractDBusInterface::toGadget(argument, application);
}
#endif
