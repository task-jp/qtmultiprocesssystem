import QtQuick 2.15
import QtMultiProcessSystem.WatchDog 1.15

Item {
    id: root
    anchors.fill: parent
    visible: enabled

    property string name
    MainThreadWatchDog {
        id: watchDog
        application: applicationManager.findByKey(root.name)
    }
    Timer {
        interval: 100 // TODO: settable
        repeat: true
        running: typeof watchDogManager !== 'undefined'
        onTriggered: {
            watchDog.pang()
        }
    }
}
