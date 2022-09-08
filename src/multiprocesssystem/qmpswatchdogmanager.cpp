#include "qmpswatchdogmanager.h"
#include "qmpsapplicationmanager.h"

class QMpsWatchDogManager::Private
{
public:
    QMpsApplicationManager applicationManager;
    static QMpsWatchDogManager *server;
};

QMpsWatchDogManager *QMpsWatchDogManager::Private::server = nullptr;

QMpsWatchDogManager::QMpsWatchDogManager(QObject *parent, Type type)
    : QMpsIpcInterface(parent, type)
    , d(type == Server ? new Private : nullptr)
{
    switch (type) {
    case Unknown:
        qFatal("Unknown type at %s(%d)", Q_FUNC_INFO, __LINE__);
        break;
    case Server:
        Private::server = this;
        d->applicationManager.init();
        connect (&d->applicationManager, &QMpsApplicationManager::applicationStatusChanged,
                 this, [this](const QMpsApplication &application, const QString &status) {
            if (status == QStringLiteral("destroyed")) {
                qDebug() << "WatchDogManager ejects" << application.key();
                this->finished(application);
            }
        });
        break;
    case Client:
        break;
    }
}

QMpsWatchDogManager::~QMpsWatchDogManager() = default;

void QMpsWatchDogManager::ping(const QString &method, const QMpsApplication &application, uint serial)
{
    const auto arg1 = Q_ARG(QString, method);
    const auto arg2 = Q_ARG(QMpsApplication, application);
    const auto arg3 = Q_ARG(uint,serial);
    QMpsIpcInterfaceCall(pingReceived, ping, arg1, arg2, arg3);
}

void QMpsWatchDogManager::pong(const QString &method, const QMpsApplication &application, uint serial)
{
    const auto arg1 = Q_ARG(QString, method);
    const auto arg2 = Q_ARG(QMpsApplication, application);
    const auto arg3 = Q_ARG(uint,serial);
    QMpsIpcInterfaceCall(pongReceived, pong, arg1, arg2, arg3);
}

void QMpsWatchDogManager::pang(const QString &method, const QMpsApplication &application)
{
    const auto arg1 = Q_ARG(QString, method);
    const auto arg2 = Q_ARG(QMpsApplication, application);
    QMpsIpcInterfaceCall(pangReceived, pang, arg1, arg2);
}

QMpsAbstractIpcInterface *QMpsWatchDogManager::server() const
{
    return Private::server;
}
