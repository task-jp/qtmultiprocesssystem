#include "qmpsapplication.h"

#include <QtCore/QMetaProperty>

class QMpsApplication::Private : public QSharedData
{
public:
    int id = 0;
    QString key;
    QString name;
    QColor theme;
    QUrl icon;
    QString area;
    bool systemUI = false;
    bool autoStart = false;
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

QString QMpsApplication::name() const
{
    return d->name;
}

void QMpsApplication::setName(const QString &name)
{
    if (this->name() == name) return;
    d->name = name;
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

bool QMpsApplication::isValid() const
{
    return d->id > 0;
}

QMpsApplication QMpsApplication::fromJson(const QJsonObject &json)
{
    QMpsApplication ret;
    for (int i = 0; i < ret.staticMetaObject.propertyCount(); i++) {
        auto property = ret.staticMetaObject.property(i);
        auto key = QString::fromLatin1(property.name());
        if (json.contains(key)) {
            auto type = property.type();
            auto value = json.value(key);
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
            default:
                qWarning() << type << key << value << "not supported";
                break;
            }
        } else {
            qWarning() << key << "not found in json";
        }
    }
    return ret;
}

QDataStream &operator<<(QDataStream &out, const QMpsApplication &application)
{
    const auto mo = application.staticMetaObject;
    for (int i = 0; i < mo.propertyCount(); i++) {
        auto property = mo.property(i);
        auto key = QString::fromLatin1(property.name());
        auto value = property.readOnGadget(&application);
        out << value;
    }
    return out;
}

QDataStream &operator>>(QDataStream &in, QMpsApplication &application)
{
    const auto mo = application.staticMetaObject;
    for (int i = 0; i < mo.propertyCount(); i++) {
        auto property = mo.property(i);
        auto key = QString::fromLatin1(property.name());
        QVariant value;
        in >> value;
        property.writeOnGadget(&application, value);
    }
    return in;
}
