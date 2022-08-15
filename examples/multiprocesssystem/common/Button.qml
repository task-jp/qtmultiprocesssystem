import QtQuick 2.15

MouseArea {
    id: root
    width: text.implicitWidth + 20
    height: 40
    property alias text: text.text
    property alias font: text.font
    property alias color: background.color
    property bool highlighted: false

    Rectangle {
        id: background
        anchors.fill: parent
        anchors.margins: 10
        radius: 10
        color: 'lightgray'
    }

    Text {
        id: text
        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.WordWrap
    }

    states: State {
        when: root.highlighted
        PropertyChanges {
            target: background
            color: 'blue'
        }
        PropertyChanges {
            target: text
            color: 'white'
        }
    }
}
