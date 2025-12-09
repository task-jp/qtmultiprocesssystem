#ifndef QMPSAPPLICATION_H
#define QMPSAPPLICATION_H

#include <QtMultiProcessSystem/multiprocesssystem_global.h>
#include <QtCore/QJsonObject>
#include <QtCore/QObject>
#include <QtCore/QUrl>
#include <QtGui/QColor>
#include <QtQml/qqml.h>

QT_BEGIN_NAMESPACE

class MULTIPROCESSSYSTEM_EXPORT QMpsApplication
{
    Q_GADGET
    QML_NAMED_ELEMENT(Application)
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    QML_ADDED_IN_VERSION(1, 0)
#endif
    Q_PROPERTY(bool valid READ isValid)
    Q_PROPERTY(QString key READ key WRITE setKey)
    Q_PROPERTY(QString role READ role WRITE setRole)
    Q_PROPERTY(QJsonObject name READ name WRITE setName)
    Q_PROPERTY(QString i18nName READ i18nName)
    Q_PROPERTY(QColor theme READ theme WRITE setTheme)
    Q_PROPERTY(QUrl icon READ icon WRITE setIcon)
    Q_PROPERTY(QUrl splash READ splash WRITE setSplash)
    Q_PROPERTY(QString area READ area WRITE setArea)
    Q_PROPERTY(QJsonObject uri_handlers READ uriHandlers WRITE setUriHandlers)
    Q_PROPERTY(Attributes attributes READ attributes WRITE setAttributes)
    Q_PROPERTY(QString status READ status WRITE setStatus)
    Q_PROPERTY(qint64 processID READ processID WRITE setProcessID)
    Q_PROPERTY(QJsonObject organization READ organization WRITE setOrganization)
public:
    enum Attribute {
        None = 0x00,
        SystemUI = 0x01,
        AutoStart = 0x02,
        Daemon = 0x04,
        FullScreen = 0x08,
        BackgroundOnAutoStart = 0x10,
        Root = 0x8000,
    };
    Q_DECLARE_FLAGS(Attributes, Attribute)
    Q_FLAG(Attributes)

    QMpsApplication();
    QMpsApplication(const QMpsApplication &);
    ~QMpsApplication();
    QMpsApplication &operator=(const QMpsApplication &);
    inline void swap(QMpsApplication &other) { return d.swap(other.d); }
    bool operator==(const QMpsApplication &other) const;
    inline bool operator!=(const QMpsApplication &other) const
    { return !operator==(other); }

    QString key() const;
    void setKey(const QString &key);

    QString role() const;
    void setRole(const QString &role);

    QJsonObject name() const;
    void setName(const QJsonObject &name);
    QString i18nName() const;

    QColor theme() const;
    void setTheme(const QColor &theme);

    QUrl icon() const;
    void setIcon(const QUrl &icon);

    QUrl splash() const;
    void setSplash(const QUrl &splash);

    QString area() const;
    void setArea(const QString &area);

    QJsonObject uriHandlers() const;
    void setUriHandlers(const QJsonObject &uriHandlers);

    Attributes attributes() const;
    void setAttributes(Attributes attributes);

    QString status() const;
    void setStatus(const QString &status);

    QJsonObject organization() const;
    void setOrganization(const QJsonObject &organization);

    qint64 processID() const;
    void setProcessID(qint64 processID);

    bool isValid() const;

    static QList<QMpsApplication> fromJson(const QJsonObject &json);

private:
    class Private;
    QSharedDataPointer<Private> d;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QMpsApplication::Attributes)


MULTIPROCESSSYSTEM_EXPORT QDataStream &operator<<(QDataStream &out, const QMpsApplication &application);
MULTIPROCESSSYSTEM_EXPORT QDataStream &operator>>(QDataStream &in, QMpsApplication &application);
MULTIPROCESSSYSTEM_EXPORT QDebug operator<<(QDebug debug, const QMpsApplication &application);

MULTIPROCESSSYSTEM_EXPORT uint qHash(const QMpsApplication &application, uint seed = 0);

Q_DECLARE_SHARED(QMpsApplication)
Q_DECLARE_METATYPE(QMpsApplication)
Q_DECLARE_METATYPE(QList<QMpsApplication>)

#if defined(QT_DBUS_LIB)
#include <QtDBus/QDBusArgument>
QDBusArgument &operator<<(QDBusArgument &argument, const QMpsApplication &application);
const QDBusArgument &operator>>(const QDBusArgument &argument, QMpsApplication &application);
#endif

QT_END_NAMESPACE

#endif // QMPSAPPLICATION_H
