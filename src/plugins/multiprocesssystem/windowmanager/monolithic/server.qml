import QtQuick 2.15
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

    property var application: applicationManager.findByKey('main')
    SystemdWatchDog {
        id: systemd
    }
    MainThreadWatchDog {
        id: main
        application: root.application
    }
    RenderThreadWatchDog {
        id: render
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
        function onActivated(application) {
            var current = applicationManager.current
            if (application === current)
                return
            if (!application.area) {
                if (current.id in root.apps) {
                    root.apps[current.id].enabled = false
                }
                applicationManager.current = application
                if (application.id in root.apps) {
                    root.apps[application.id].enabled = true
                    return
                }
            }
            var url = 'qrc:/multiprocesssystem/%1/%1.qml'.arg(application.key)
            var parent = root.findParent(application)
            var item = chromeComponent.createObject(parent, {"source": url})
            if (!application.area) {
                root.apps[application.id] = item
                item.item.enabled = true
            }
        }
    }
}
