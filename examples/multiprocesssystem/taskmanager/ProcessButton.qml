import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtMultiProcessSystem 1.15 as MPS
import QtMultiProcessSystem.ApplicationManager 1.15
import '../common/'

MouseArea {
    id: root
    property string status
    signal launch
    signal kill

    Rectangle {
        id: background
        anchors.fill: parent
        anchors.margins: 10
        color: 'tomato'
        opacity: 0.25
    }

    Text {
        id: caption
        anchors.centerIn: parent
        text: 'Kill'
        font.pixelSize: 32
    }

    onClicked: root.kill()
    states: [
        State {
            when: root.status !== 'started'
            PropertyChanges {
                target: root
                onClicked: root.launch()
            }
            PropertyChanges {
                target: background
                color: 'green'
            }
            PropertyChanges {
                target: caption
                text: 'Launch'
            }
        }
    ]
}
