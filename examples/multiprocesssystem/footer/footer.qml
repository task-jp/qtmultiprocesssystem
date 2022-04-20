import QtQuick 2.15
import '../common/'

AbstractMain {
    id: root

    Text {
        id: clock
        anchors.centerIn: parent
        font.pixelSize: 60
    }

    Timer {
        id: timer
        running: true
        interval: 250
        repeat: true
        onTriggered: clock.text = Qt.formatDateTime(new Date, 'yyyy-MM-dd hh:mm:ss')
    }
}
