import QtQuick 2.15
import QtMultiProcessSystem.WatchDog 1.15

Item {
    id: root
    anchors.fill: parent
    visible: enabled

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
        interval: 100 // TODO: settable
        repeat: true
        running: typeof watchDogManager !== 'undefined' && Qt.application.name !== 'system'
        onTriggered: {
            systemd.pang()
            main.pang()
            render.pang()
        }
    }
}
