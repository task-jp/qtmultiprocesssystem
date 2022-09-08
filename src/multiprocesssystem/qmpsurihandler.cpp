#include "qmpsurihandler.h"
#include "qmpsapplicationmanager.h"
#include <QtGui/QDesktopServices>

class QMpsUriHandler::Private
{
public:
    QMpsApplicationManager applicationManager;
    QMpsApplication application;
    static QMpsUriHandler *server;
};

QMpsUriHandler *QMpsUriHandler::Private::server = nullptr;

QMpsUriHandler::QMpsUriHandler(QObject *parent, Type type)
    : QMpsIpcInterface(parent, type)
    , d(new Private)
{
    auto handle = [](const QMpsApplication &application, const QString &uri) {
        const auto uriHandlers = application.uriHandlers();
        for (auto it = uriHandlers.constBegin(); it != uriHandlers.constEnd(); ++it) {
            const auto key = it.key();
            const auto value = it.value().toString();
            if (value == QStringLiteral("scheme")) {
                if (uri.startsWith(key)) {
                    return true;
                }
            } else if (value == QStringLiteral("regexp")) {
                QRegularExpression regexp(key);
                if (regexp.match(uri).hasMatch()) {
                    return true;
                }
            }
        }
        return false;
    };

    switch (type) {
    case Unknown:
        qFatal("Unknown type at %s(%d)", Q_FUNC_INFO, __LINE__);
        break;
    case Server:
        Private::server = this;
        connect(this, &QMpsUriHandler::doOpen, this, [this, &handle](const QString &uri) {
            const auto apps = d->applicationManager.applications();
            bool handled = false;
            for (const auto &app : apps) {
                if (handle(app, uri)) {
                    handled = true;
                    d->applicationManager.exec(app, {uri});
                }
            }
            if (!handled) {
                QDesktopServices::openUrl(QUrl(uri));
            }
        });
        break;
    case Client:
        connect(this, &QMpsUriHandler::doOpen, this, [this, &handle](const QString &uri) {
            if (handle(d->application, uri)) {
                emit requested(uri);
            }
        });
        break;
    }
    init();
}

QMpsUriHandler::~QMpsUriHandler() = default;

bool QMpsUriHandler::init()
{
    if (!QMpsIpcInterface::init())
        return false;
    switch (type()) {
    case Server:
        if (!d->applicationManager.init())
            return false;
    default:
        break;
    }
    return true;
}

QMpsApplication QMpsUriHandler::application() const
{
    return d->application;
}

void QMpsUriHandler::setApplication(const QMpsApplication &application)
{
    if (d->application == application) return;
    d->application = application;
    emit applicationChanged(application);
}

void QMpsUriHandler::open(const QString &uri)
{
    const auto arg1 = Q_ARG(QString, uri);
    QMpsIpcInterfaceCall(doOpen, open, arg1);
}

QMpsAbstractIpcInterface *QMpsUriHandler::server() const
{
    return Private::server;
}
