#ifndef QMPSAPPLICATION_H
#define QMPSAPPLICATION_H

#include "multiprocesssystem_global.h"
#include <QtCore/QJsonObject>
#include <QtCore/QObject>
#include <QtCore/QUrl>
#include <QtGui/QColor>

class MULTIPROCESSSYSTEM_EXPORT QMpsApplication
{
    Q_GADGET
    Q_PROPERTY(int id READ id WRITE setID)
    Q_PROPERTY(QString key READ key WRITE setKey)
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QColor theme READ theme WRITE setTheme)
    Q_PROPERTY(QUrl icon READ icon WRITE setIcon)
    Q_PROPERTY(QString area READ area WRITE setArea)
    Q_PROPERTY(bool systemUI READ isSystemUI WRITE setSystemUI)
    Q_PROPERTY(bool autoStart READ isAutoStart WRITE setAutoStart)
public:
    QMpsApplication();
    QMpsApplication(const QMpsApplication &);
    ~QMpsApplication();
    QMpsApplication &operator=(const QMpsApplication &);
    inline void swap(QMpsApplication &other) { return d.swap(other.d); }
    bool operator==(const QMpsApplication &other) const;
    inline bool operator!=(const QMpsApplication &other) const
    { return !operator==(other); }

    int id() const;
    void setID(int id);

    QString key() const;
    void setKey(const QString &key);

    QString name() const;
    void setName(const QString &name);

    QColor theme() const;
    void setTheme(const QColor &theme);

    QUrl icon() const;
    void setIcon(const QUrl &icon);

    QString area() const;
    void setArea(const QString &area);

    bool isSystemUI() const;
    void setSystemUI(bool systemUI);

    bool isAutoStart() const;
    void setAutoStart(bool autoStart);

    bool isValid() const;

    static QMpsApplication fromJson(const QJsonObject &json);

private:
    class Private;
    QSharedDataPointer<Private> d;
};

MULTIPROCESSSYSTEM_EXPORT QDataStream &operator<<(QDataStream &out, const QMpsApplication &application);
MULTIPROCESSSYSTEM_EXPORT QDataStream &operator>>(QDataStream &in, QMpsApplication &application);


Q_DECLARE_SHARED(QMpsApplication)
Q_DECLARE_METATYPE(QMpsApplication)

#endif // QMPSAPPLICATION_H
