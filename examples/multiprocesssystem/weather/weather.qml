import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: root
    anchors.fill: parent
    visible: enabled
    Label {
        anchors.centerIn: parent
        text: 'Weather'
        font.pixelSize: 64
    }
}
