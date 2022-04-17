#include <QtCore/QCommandLineParser>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickWindow>
#include <QtMultiProcessSystem/QMpsApplicationManagerFactory>
#include <QtMultiProcessSystem/QMpsApplicationManager>
#include <QtMultiProcessSystem/QMpsWindowManagerFactory>
#include <QtMultiProcessSystem/QMpsWindowManager>
#include <QtMultiProcessSystem/QMpsWatchDogManagerFactory>
#include <QtMultiProcessSystem/QMpsWatchDogManager>
#include <QtMultiProcessSystem/QMpsApplicationFactory>
#include <QtMultiProcessSystem/QMpsApplication>

int main(int argc, char *argv[])
{
    qSetMessagePattern("[%{if-debug}D%{endif}%{if-info}I%{endif}%{if-warning}W%{endif}%{if-critical}C%{endif}%{if-fatal}F%{endif}] %{function}:%{line} - %{message}");
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts, true);
    QGuiApplication app(argc, argv);

    QCommandLineParser parser;
    QCommandLineOption appManOption({{"a", "application-manager"}, "Application Manager Backend", "inprocess"});
    parser.addOption(appManOption);
    QCommandLineOption winManOption({{"w", "window-manager"}, "Window Manager Backend", "monolithic"});
    parser.addOption(winManOption);
    QCommandLineOption watManOption({{"d", "watchdog-manager"}, "WatchDogManager Backend", "none"});
    parser.addOption(watManOption);
    parser.addPositionalArgument("app", "application to launch");
    parser.process(app);
    auto args = parser.positionalArguments();

    QQmlApplicationEngine engine;
    auto context = engine.rootContext();
    auto type = args.isEmpty() ? QMpsAbstractManagerFactory::Server : QMpsAbstractManagerFactory::Client;

    QString appManType = QLatin1String("inprocess");
    if (parser.isSet(appManOption)) {
        appManType = parser.value(appManOption);
    } else if (qEnvironmentVariableIsSet("QT_MULTIPROCESSSYSTEM_APPLICATIONMANAGER")) {
        appManType = qEnvironmentVariable("QT_MULTIPROCESSSYSTEM_APPLICATIONMANAGER");
    }

    QMpsApplicationManager *applicationManager = nullptr;
    QString prefix = QLatin1String("example/");
    if (QMpsApplicationManagerFactory::keys().contains(appManType.toLower())) {
        switch (type) {
        case QMpsAbstractManagerFactory::Server:
            applicationManager = QMpsApplicationManagerFactory::create(appManType, &app, type);
            break;
        case QMpsAbstractManagerFactory::Client:
            applicationManager = new QMpsApplicationManager(&app, type);
        }
        applicationManager->init();
        if (type == QMpsAbstractManagerFactory::Server) {
            auto apps = QMpsApplicationFactory::apps(prefix);
            std::sort(apps.begin(), apps.end(), [](const QMpsApplication &a, const QMpsApplication &b) {
                return a.id() < b.id();
            });
            applicationManager->setApplications(apps);
        }
        context->setContextProperty("applicationManager", applicationManager);
    } else {
        qFatal("Application Manager backend '%s' not found in %s", qUtf8Printable(appManType), qUtf8Printable(QMpsApplicationManagerFactory::keys().join(", ")));
    }

    QString winManType = QLatin1String("monolithic");
    if (parser.isSet(winManOption)) {
        winManType = parser.value(winManOption);
    } else if (qEnvironmentVariableIsSet("QT_MULTIPROCESSSYSTEM_WINDOWMANAGER")) {
        winManType = qEnvironmentVariable("QT_MULTIPROCESSSYSTEM_WINDOWMANAGER");
    }
    if (QMpsWindowManagerFactory::keys().contains(winManType.toLower())) {
        QMpsWindowManagerFactory::create(winManType, type, &app);
    } else {
        qFatal("Window Manager backend '%s' not found in %s", qUtf8Printable(winManType), qUtf8Printable(QMpsWindowManagerFactory::keys().join(", ")));
    }

    QString watManType = QLatin1String("none");
    if (parser.isSet(watManOption)) {
        watManType = parser.value(watManOption);
    } else if (qEnvironmentVariableIsSet("QT_MULTIPROCESSSYSTEM_WATCHDOGMANAGER")) {
        watManType = qEnvironmentVariable("QT_MULTIPROCESSSYSTEM_WATCHDOGMANAGER");
    }
    if (QMpsWatchDogManagerFactory::keys().contains(watManType.toLower())) {
        context->setContextProperty("watchDogManager", QMpsWatchDogManagerFactory::create(watManType, type, &app));
    } else if (watManType.toLower() != "none") {
        qFatal("WatchDog Manager backend '%s' not found in %s", qUtf8Printable(watManType), qUtf8Printable(QMpsWatchDogManagerFactory::keys().join(", ")));
    }

    QString role = QLatin1String("system");
    if (!args.isEmpty()) {
        role = args.first();
    }
    app.setApplicationName(role);

    QUrl url;
    if (type == QMpsAbstractManagerFactory::Server) {
        url = QUrl(QStringLiteral("qrc:/multiprocesssystem/server.qml"));
        if (winManType == QLatin1String("monolithic")) {
            for (const auto &application : applicationManager->applications()) {
                QMpsApplicationFactory::load(prefix + application.key(), &app);
            }
        }
        qmlRegisterType(QUrl(QStringLiteral("qrc:/multiprocesssystem/%1/%1.qml").arg(role)), "QtMultiProcessSystem.Internal", 1, 0, "Main");
    } else {
        const auto apps = QMpsApplicationFactory::apps(prefix + role);
        Q_ASSERT(apps.count() == 1);
        if (apps.first().isDaemon()) {
            url = QUrl(QStringLiteral("qrc:/multiprocesssystem/%1/%1.qml").arg(role));
        } else {
            url = QUrl(QStringLiteral("qrc:/multiprocesssystem/client.qml"));
            qmlRegisterType(QUrl(QStringLiteral("qrc:/multiprocesssystem/%1/%1.qml").arg(role)), "QtMultiProcessSystem.Internal", 1, 0, "Main");
        }
        QMpsApplicationFactory::load(prefix + role, &app);
    }
    qDebug() << url;

    qDebug() << role << appManType << winManType << type;

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [&](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
        auto window = qobject_cast<QQuickWindow *>(obj);
        if (window) {
            window->setTitle(role);
        }
        if (type == QMpsAbstractManagerFactory::Server)
            applicationManager->start();
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
