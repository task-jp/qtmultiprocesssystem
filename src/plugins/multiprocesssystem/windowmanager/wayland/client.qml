import QtQuick 2.15
import QtQuick.Window 2.15
import QtMultiProcessSystem.Internal 1.0

Window {
    id: root
    visible: true
    color: 'transparent'

    Main {
        id: main
        anchors.fill: parent
        application: applicationManager.findByKey(Qt.application.name)
    }
}
