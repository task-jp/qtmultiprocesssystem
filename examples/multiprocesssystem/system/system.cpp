#include <QtCore/QCommandLineParser>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtMultiProcessSystem/QMpsApplicationManagerFactory>
#include <QtMultiProcessSystem/QMpsApplicationManager>
#include <QtMultiProcessSystem/QMpsWindowManagerFactory>
#include <QtMultiProcessSystem/QMpsWindowManager>
#include <QtMultiProcessSystem/QMpsApplicationFactory>
#include <QtMultiProcessSystem/QMpsApplication>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QCommandLineParser parser;
    QCommandLineOption appManOption({{"a", "application-manager"}, "Application Manager Backend", "inprocess"});
    parser.addOption(appManOption);
    QCommandLineOption winManOption({{"w", "window-manager"}, "Window Manager Backend", "native"});
    parser.addOption(winManOption);
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

    if (QMpsApplicationManagerFactory::keys().contains(appManType.toLower())) {
        context->setContextProperty("applicationManager", QMpsApplicationManagerFactory::create(appManType, type, &app));
    } else {
        qFatal("Application Manager backend '%s' not found", qUtf8Printable(appManType));
    }
    qputenv("QT_MULTIPROCESSSYSTEM_APPLICATIONMANAGER", appManType.toUtf8());

    QString winManType = QLatin1String("monolithic");
    if (parser.isSet(winManOption)) {
        winManType = parser.value(winManOption);
    } else if (qEnvironmentVariableIsSet("QT_MULTIPROCESSSYSTEM_WINDOWMANAGER")) {
        winManType = qEnvironmentVariable("QT_MULTIPROCESSSYSTEM_WINDOWMANAGER");
    }
    if (QMpsWindowManagerFactory::keys().contains(winManType.toLower())) {
        QMpsWindowManagerFactory::create(winManType, type, &app);
    } else {
        qFatal("Window Manager backend '%s' not found", qUtf8Printable(winManType));
    }
    qputenv("QT_MULTIPROCESSSYSTEM_WINDOWMANAGER", winManType.toUtf8());

    QString role = QLatin1String("system");
    if (!args.isEmpty()) {
        role = args.first();
    }

    QString prefix = QLatin1String("example/");
    QUrl url;
    if (type == QMpsAbstractManagerFactory::Server) {
        url = QUrl(QStringLiteral("qrc:/multiprocesssystem/server.qml"));
        if (appManType == QLatin1String("inprocess")) {
            for (const auto &name : QMpsApplicationFactory::keys()) {
                if (name.startsWith(prefix))
                    QMpsApplicationFactory::load(name, &app);
            }
        }
    } else {
        url = QUrl(QStringLiteral("qrc:/multiprocesssystem/client.qml"));
        qDebug() << role;
        QMpsApplicationFactory::load(prefix + role, &app);
    }
    qDebug() << url;

    qDebug() << role << appManType << winManType << type;
    qmlRegisterType(QUrl(QStringLiteral("qrc:/multiprocesssystem/%1/%1.qml").arg(role)), "QtMultiProcessSystem.Internal", 1, 0, "Main");

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
