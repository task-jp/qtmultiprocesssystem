import QtQuick 2.15
import QtMultiProcessSystem 1.15 as MPS
import QtMultiProcessSystem.Internal 1.0
import QtMultiProcessSystem.WatchDog 1.15

Main {
    id: root

    Component {
        id: chromeComponent
        Loader {
            anchors.fill: parent
        }
    }

    property var application: applicationManager.findByKey(Qt.application.name)
    SystemdWatchDog {
        id: systemd
    }
    MainThreadWatchDog {
        id: main
        manager: typeof watchDogManager === 'undefined' ? null : watchDogManager
        application: root.application
    }
    RenderThreadWatchDog {
        id: render
        manager: typeof watchDogManager === 'undefined' ? null : watchDogManager
        application: root.application
    }
    Timer {
        running: true
        repeat: true
        interval: 100 // TODO: settable
        onTriggered: systemd.pang()
    }
    Timer {
        interval: 100 // TODO: settable
        repeat: true
        running: typeof watchDogManager !== 'undefined'
        onTriggered: {
            main.pang()
            render.pang()
        }
    }

    property var apps: ({})
    Connections {
        target: applicationManager
        function onActivated(application, args) {
            var current = applicationManager.current
            if (application.key === current.key)
                return
            if (!application.area && !(application.attributes & MPS.Application.Daemon)) {
                if (args.includes("--background")) {
                    if (application.key in root.apps) {
                        return
                    }
                } else {
                    if (current.key in root.apps) {
                        root.apps[current.key].enabled = false
                    }
                    applicationManager.current = application
                    if (application.key in root.apps) {
                        root.apps[application.key].enabled = true
                        return
                    }
                }
            }
            var url = 'qrc:/multiprocesssystem/%1/%1.qml'.arg(application.key)
            var parent = root.findParent(application)
            var item = chromeComponent.createObject(parent, {"source": url}).item
            if (!application.area && !(application.attributes & MPS.Application.Daemon)) {
                root.apps[application.key] = item
                item.application = application
                if (args.includes("--background")) {
                    item.enabled = false
                } else {
                    item.enabled = true
                }
                if (typeof item.activated === 'function')
                    item.activated(args)
                }
            }
        }
        function onKilled(application) {
            var item = root.apps[application.key]
            item.parent.destroy()
            delete root.apps[application.key]
        }
    }
}
