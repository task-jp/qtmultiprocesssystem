#include "qmpsurihandler.h"

class QMpsUriHandler::Private
{
public:
    QMpsApplication application;
    static QMpsUriHandler *server;
};

QMpsUriHandler *QMpsUriHandler::Private::server = nullptr;

QMpsUriHandler::QMpsUriHandler(const QMpsApplication &application, QObject *parent, Type type)
    : QMpsIpcInterface(parent, type)
    , d(new Private {application})
{
    switch (type) {
    case Server:
        Private::server = this;
        break;
    case Client:
        connect(this, &QMpsUriHandler::doOpen, this, [this](const QString &uri) {
            const auto uriHandlers = d->application.uriHandlers();
            for (auto it = uriHandlers.constBegin(); it != uriHandlers.constEnd(); ++it) {
                const auto key = it.key();
                const auto value = it.value().toString();
                if (value == QStringLiteral("scheme")) {
                    if (uri.startsWith(key)) {
                        emit requested(uri);
                        break;
                    }
                } else if (value == QStringLiteral("regexp")) {
                    QRegularExpression regexp(key);
                    if (regexp.match(uri).hasMatch()) {
                        emit requested(uri);
                        break;
                    }
                }
            }
        });
        break;
    }
}

QMpsUriHandler::~QMpsUriHandler() = default;

QMpsApplication QMpsUriHandler::application() const
{
    return d->application;
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
