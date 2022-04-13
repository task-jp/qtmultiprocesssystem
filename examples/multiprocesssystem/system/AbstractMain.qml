import QtQuick 2.15
import QtMultiProcessSystem.WatchDog 1.15

Item {
    id: root
    anchors.fill: parent
    visible: enabled

    property string name
    MainThreadWatchDog {
        application: applicationManager.findByKey(root.name)
    }
}
