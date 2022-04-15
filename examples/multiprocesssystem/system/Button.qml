import QtQuick 2.15

MouseArea {
    id: root
    width: text.implicitWidth + 20
    height: 40
    property alias text: text.text
    property alias font: text.font
    property bool highlighted: false

    Rectangle {
        id: background
        anchors.fill: parent
        anchors.margins: 10
        radius: 10
        color: root.highlighted ? 'blue' : 'lightgray'
    }

    Text {
        id: text
        anchors.centerIn: parent
        color: root.highlighted ? 'white' : 'black'
    }
}
