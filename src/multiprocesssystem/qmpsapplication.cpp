#include "qmpsapplication.h"

#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QMetaEnum>
#include <QtCore/QMetaProperty>
#include <QtCore/QLocale>

class QMpsApplication::Private : public QSharedData
{
public:
    QString key;
    QString role;
    QJsonObject name;
    QColor theme;
    QUrl icon;
    QUrl splash;
    QString area;
    QJsonObject uriHandlers;
    Attributes attributes = None;
    QString status = QStringLiteral("none");
    QJsonObject organization;
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
    return d->key == other.d->key;
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

QString QMpsApplication::role() const
{
    return d->role;
}
void QMpsApplication::setRole(const QString &role)
{
    if (this->role() == role) return;
    d->role = role;
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
    const auto locale = QLocale::system();
    for (const auto &lang : locale.uiLanguages()) {
        if (d->name.contains(lang))
            return d->name.value(lang).toString();
    }
    return d->name.value(QStringLiteral("default")).toString();
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

QUrl QMpsApplication::splash() const
{
    return d->splash;
}

void QMpsApplication::setSplash(const QUrl &splash)
{
    if (this->splash() == splash) return;
    d->splash = splash;
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

QJsonObject QMpsApplication::uriHandlers() const
{
    return d->uriHandlers;
}

void QMpsApplication::setUriHandlers(const QJsonObject &uriHandlers)
{
    if (this->uriHandlers() == uriHandlers) return;
    d->uriHandlers = uriHandlers;
}

QMpsApplication::Attributes QMpsApplication::attributes() const
{
    return d->attributes;
}

void QMpsApplication::setAttributes(Attributes attributes)
{
    if (this->attributes() == attributes) return;
    d->attributes = attributes;
}

QString QMpsApplication::status() const
{
    return d->status;
}

void QMpsApplication::setStatus(const QString &status)
{
    if (this->status() == status) return;
    d->status = status;
}

QJsonObject QMpsApplication::organization() const
{
    return d->organization;
}

void QMpsApplication::setOrganization(const QJsonObject &organization)
{
    if (this->organization() == organization) return;
    d->organization = organization;
}

bool QMpsApplication::isValid() const
{
    return !d->key.isNull();
}

QList<QMpsApplication> QMpsApplication::fromJson(const QJsonObject &json)
{
    QMpsApplication app;
    const auto mo = QMpsApplication::staticMetaObject;
    for (int i = 0; i < mo.propertyCount(); i++) {
        const auto property = mo.property(i);
        const auto key = QString::fromLatin1(property.name());
        if (json.contains(key)) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
            const int type = property.type();
#else
            const int type = property.typeId();
#endif
            const auto value = json.value(key);
            switch (type) {
            case QVariant::Bool:
                property.writeOnGadget(&app, value.toBool());
                break;
            case QVariant::Int:
                switch (value.type()) {
                case QJsonValue::Double:
                    property.writeOnGadget(&app, value.toInt());
                    break;
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
                case QJsonValue::Array: {
                    // Special case for flags
                    int attrs = None;
                    const auto array = value.toArray();
                    QMetaEnum e = mo.enumerator(mo.indexOfEnumerator("Attributes"));
                    for (const auto &v : array) {
                        const auto name = v.toString();
                        for (int i = 0; i < e.keyCount(); i++) {
                            if (name == QString::fromUtf8(e.key(i))) {
                                attrs |= e.value(i);
                            }
                        }
                    }
                    property.writeOnGadget(&app, attrs);
                    break; }
#endif
                default:
                    qWarning() << type << key << value << "not supported";
                    break;
                }
                break;
            case QVariant::String:
                property.writeOnGadget(&app, value.toString());
                break;
            case QVariant::Color:
                property.writeOnGadget(&app, QColor(value.toString()));
                break;
            case QVariant::Url:
                property.writeOnGadget(&app, QUrl(value.toString()));
                break;
            case QVariant::DateTime:
                property.writeOnGadget(&app, QDateTime::fromString(value.toString(), Qt::ISODateWithMs));
                break;
            case QMetaType::QJsonObject:
                switch (value.type()) {
                case QJsonValue::Object:
                    property.writeOnGadget(&app, value.toObject());
                    break;
                case QJsonValue::String:
                    property.writeOnGadget(&app, QJsonObject {{QStringLiteral("default"), value.toString() }});
                    break;
                default:
                    qWarning() << type << key << value << "not supported";
                    break;
                }

                break;
            default:
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
                if (type == qMetaTypeId<QMpsApplication::Attributes>()) {
                    QMpsApplication::Attributes attrs = None;
                    const auto array = value.toArray();
                    QMetaEnum e = mo.enumerator(mo.indexOfEnumerator("Attributes"));
                    for (const auto &v : array) {
                        const auto name = v.toString();
                        for (int i = 0; i < e.keyCount(); i++) {
                            if (name == QString::fromUtf8(e.key(i))) {
                                attrs |= static_cast<QMpsApplication::Attribute>(e.value(i));
                            }
                        }
                    }
                    property.writeOnGadget(&app, QVariant::fromValue(attrs));
                    break;
                }
#endif
                qWarning() << type << key << value << "not supported";
                break;
            }
//        } else {
//            qWarning() << key << "not found in json";
        }
    }

    if (app.role().isEmpty()) {
        app.setRole(app.key());
    }
    QList<QMpsApplication> ret;
    ret.append(app);

    if (json.contains(QStringLiteral("alias"))) {
        auto value = json.value(QStringLiteral("alias"));
        if (value.type() == QJsonValue::Array) {
            for (const QJsonValue &v : value.toArray()) {
                if (v.type() == QJsonValue::String) {
                    QString alias = v.toString();
                    app.setKey(alias);
                    ret.append(app);
                }
            }
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
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        const int type = property.type();
#else
        const int type = property.typeId();
#endif
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
    return qHash(application.key(), seed);
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
